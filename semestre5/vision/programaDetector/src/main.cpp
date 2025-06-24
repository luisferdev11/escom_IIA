#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <limits>
#include "../include/imagen_bmp.h"
#include "../include/lector_bmp.h"

// Alias para mejorar la legibilidad
using Matriz = std::vector<std::vector<int>>;
using DatosEntrenamiento = std::map<int, std::vector<Matriz>>;
using MatrizAcumulada = std::map<int, Matriz>;

// Función para convertir una ImagenBMP a una matriz de pesos (0s y 1s)
Matriz crearMatrizDePesos(const ImagenBMP& bmp) {
    const int ancho = bmp.obtenerAncho();
    const int alto = bmp.obtenerAlto();
    const int conteo_bits = bmp.obtenerConteoBits();
    const int bytes_por_pixel = conteo_bits / 8;

    Matriz matriz_pesos(alto, std::vector<int>(ancho, 0));
    const std::vector<uint8_t>& pixeles = bmp.obtenerPixeles();

    const int umbral = 5;

    for (int y = 0; y < alto; ++y) {
        for (int x = 0; x < ancho; ++x) {
            const int indice = (y * ancho + x) * bytes_por_pixel;
            const uint8_t azul = pixeles[indice + 0];
            const uint8_t verde = (bytes_por_pixel > 1) ? pixeles[indice + 1] : 0;
            const uint8_t rojo = (bytes_por_pixel > 2) ? pixeles[indice + 2] : 0;
            const int promedio_color = (static_cast<int>(rojo) + verde + azul) / 3;

            if (promedio_color > umbral) {
                matriz_pesos[y][x] = 1;
            }
        }
    }
    return matriz_pesos;
}

// Carga todas las imágenes de entrenamiento y las convierte a matrices de pesos
DatosEntrenamiento cargarDatosDeEntrenamiento(const std::string& ruta_datos) {
    DatosEntrenamiento datos_por_digito;
    for (const auto& entrada_dir : std::filesystem::directory_iterator(ruta_datos)) {
        if (entrada_dir.is_directory()) {
            const std::string nombre_carpeta = entrada_dir.path().filename().string();
            int numero_digito = -1;
            try {
                numero_digito = std::stoi(nombre_carpeta);
            } catch (...) { continue; }

            for (const auto& entrada_archivo : std::filesystem::directory_iterator(entrada_dir.path())) {
                if (entrada_archivo.is_regular_file() && entrada_archivo.path().extension() == ".bmp") {
                    try {
                        auto imagen_bmp = LectorBMP::leerBMP(entrada_archivo.path().string());
                        auto matriz = crearMatrizDePesos(*imagen_bmp);
                        datos_por_digito[numero_digito].push_back(matriz);
                    } catch (const std::exception& e) {
                        std::cerr << "Error al leer '" << entrada_archivo.path().string() << "': " << e.what() << std::endl;
                    }
                }
            }
        }
    }
    return datos_por_digito;
}

// Suma dos matrices, útil para el método del perceptrón
void sumarMatrices(Matriz& destino, const Matriz& fuente) {
    for (size_t i = 0; i < destino.size(); ++i) {
        for (size_t j = 0; j < destino[i].size(); ++j) {
            destino[i][j] += fuente[i][j];
        }
    }
}

// Crea una matriz "promedio" para cada dígito
MatrizAcumulada crearMatrizAcumulada(const DatosEntrenamiento& todos_los_digitos) {
    MatrizAcumulada acumuladas;
    for (const auto& par : todos_los_digitos) {
        const int digito = par.first;
        const auto& matrices = par.second;
        if (!matrices.empty()) {
            acumuladas[digito] = matrices[0];
            for (size_t i = 1; i < matrices.size(); ++i) {
                sumarMatrices(acumuladas[digito], matrices[i]);
            }
        }
    }
    return acumuladas;
}

// --- MÉTODOS DE RECONOCIMIENTO ---

// 1. Método Exhaustivo: Busca una coincidencia exacta.
int metodoExhaustivo(const Matriz& matriz_prueba, const DatosEntrenamiento& datos_entrenamiento) {
    for (const auto& par : datos_entrenamiento) {
        const int digito = par.first;
        for (const auto& matriz_entrenamiento : par.second) {
            if (matriz_prueba == matriz_entrenamiento) {
                return digito;
            }
        }
    }
    return -1; // No encontrado
}

// 2. Método de Probabilidades: Busca la mayor similitud.
std::pair<int, double> metodoProbabilidades(const Matriz& matriz_prueba, const DatosEntrenamiento& datos_entrenamiento) {
    int mejor_digito = -1;
    double mejor_coincidencia = -1.0;

    const size_t filas = matriz_prueba.size();
    const size_t columnas = (filas > 0) ? matriz_prueba[0].size() : 0;
    const size_t total_pixeles = filas * columnas;

    for (const auto& par : datos_entrenamiento) {
        const int digito = par.first;
        for (const auto& matriz_entrenamiento : par.second) {
            if (matriz_entrenamiento.size() != filas || matriz_entrenamiento[0].size() != columnas) continue;
            
            size_t coincidencias = 0;
            for (size_t f = 0; f < filas; ++f) {
                for (size_t c = 0; c < columnas; ++c) {
                    if (matriz_prueba[f][c] == matriz_entrenamiento[f][c]) {
                        coincidencias++;
                    }
                }
            }
            const double porcentaje = (total_pixeles == 0) ? 0.0 : (100.0 * coincidencias / total_pixeles);
            if (porcentaje > mejor_coincidencia) {
                mejor_coincidencia = porcentaje;
                mejor_digito = digito;
            }
        }
    }
    return {mejor_digito, mejor_coincidencia};
}

// 3. Método del Perceptrón: Usa plantillas acumuladas.
int metodoPerceptron(const Matriz& matriz_prueba, const MatrizAcumulada& matrices_acumuladas, long long umbral) {
    int mejor_digito = -1;
    long long suma_maxima = std::numeric_limits<long long>::lowest();

    const size_t filas = matriz_prueba.size();
    const size_t columnas = (filas > 0) ? matriz_prueba[0].size() : 0;

    for (const auto& par : matrices_acumuladas) {
        const int digito = par.first;
        const auto& matriz_digito = par.second;
        if (matriz_digito.size() != filas || matriz_digito[0].size() != columnas) continue;

        long long suma_ponderada = 0;
        for (size_t f = 0; f < filas; ++f) {
            for (size_t c = 0; c < columnas; ++c) {
                suma_ponderada += static_cast<long long>(matriz_prueba[f][c]) * matriz_digito[f][c];
            }
        }

        if (suma_ponderada >= umbral && suma_ponderada > suma_maxima) {
            suma_maxima = suma_ponderada;
            mejor_digito = digito;
        }
    }
    return mejor_digito;
}


int main() {
    try {
        // Rutas a nuestros datos
        const std::string ruta_entrenamiento = "datos/entrenamiento";
        const std::string ruta_prueba = "datos/prueba/test.bmp";

        // 1. Cargar y procesar datos de entrenamiento
        std::cout << "Cargando datos de entrenamiento..." << std::endl;
        const auto datos_entrenamiento = cargarDatosDeEntrenamiento(ruta_entrenamiento);
        const auto matrices_acumuladas = crearMatrizAcumulada(datos_entrenamiento);
        std::cout << "¡Carga completa!" << std::endl;

        // 2. Cargar imagen de prueba
        std::cout << "\nCargando imagen de prueba: " << ruta_prueba << std::endl;
        const auto bmp_prueba = LectorBMP::leerBMP(ruta_prueba);
        const auto matriz_prueba = crearMatrizDePesos(*bmp_prueba);

        // 3. Aplicar métodos de reconocimiento e imprimir resultados
        std::cout << "\n--- Resultados del Reconocimiento ---" << std::endl;

        // Método Exhaustivo
        const int resultado_ex = metodoExhaustivo(matriz_prueba, datos_entrenamiento);
        if (resultado_ex < 0) {
            std::cout << "[Exhaustivo] No se encontró una coincidencia exacta." << std::endl;
        } else {
            std::cout << "[Exhaustivo] El dígito es: " << resultado_ex << " (coincidencia exacta)." << std::endl;
        }

        // Método de Probabilidades
        const auto resultado_prob = metodoProbabilidades(matriz_prueba, datos_entrenamiento);
        std::cout << "[Probabilidad] El dígito es: " << resultado_prob.first 
                  << " (con una similitud del " << resultado_prob.second << "%)." << std::endl;

        // Método del Perceptrón
        const long long umbral_perceptron = 200;
        const int resultado_perc = metodoPerceptron(matriz_prueba, matrices_acumuladas, umbral_perceptron);
        if (resultado_perc < 0) {
            std::cout << "[Perceptrón] Ningún dígito superó el umbral." << std::endl;
        } else {
            std::cout << "[Perceptrón] El dígito es: " << resultado_perc << "." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Ocurrió un error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} 