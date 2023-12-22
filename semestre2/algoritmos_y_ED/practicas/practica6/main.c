/**
 * Nombres: Rodriguez Dominguez Luis Fernando y Montes de oca Arellano Edgar
 * Grupo: 2BV2
 * Carrera: Ingeniería en Inteligencia Artificial
 * Fecha de última modificación: 19:56 hrs 10/11/23
 */

#include <time.h>
#include <unistd.h>

#include "bicola.h"

/**
 * @brief Crea el nodo a usar.
 *
 * @param archivo Nombre del archivo a enviar.
 *
 * @return nodo Nodo creado.
 */

Nodo* crearNodo(char* archivo) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    strcpy(nuevo->archivo, archivo);
    nuevo->siguiente = NULL;
    return nuevo;
}

/**
 * @brief Inicializa una bicola.
 *
 * @param cola Puntero a la bicola a inicializar.
 */
void inicializarBicola(Bicola* cola) {
    cola->inicio = NULL;
    cola->fin = NULL;
    cola->contador = 0;
}

/**
 * @brief Verifica si la bicola está vacía.
 *
 * @param cola Puntero a la bicola a verificar.
 * @return int 1 si la bicola está vacía, 0 en caso contrario.
 */
int estaVacia(Bicola* cola) {
    return cola->contador == 0;
}

/**
 * @brief Ingresa un nodo por la derecha en la bicola.
 *
 * @param cola Puntero a la bicola.
 * @param archivo Nombre del archivo a agregar en el nodo.
 */
void ingresarDerecha(Bicola* cola, char* archivo) {
    Nodo* nuevo = crearNodo(archivo);
    if (estaVacia(cola)) {
        cola->inicio = cola->fin = nuevo;
    } else {
        cola->fin->siguiente = nuevo;
        cola->fin = nuevo;
    }
    cola->contador++;
}

/**
 * @brief Ingresa un nodo por la izquierda en la bicola.
 *
 * @param cola Puntero a la bicola.
 * @param archivo Nombre del archivo a agregar en el nodo.
 */
void ingresarIzquierda(Bicola* cola, char* archivo) {
    Nodo* nuevo = crearNodo(archivo);
    if (estaVacia(cola)) {
        cola->inicio = cola->fin = nuevo;
    } else {
        nuevo->siguiente = cola->inicio;
        cola->inicio = nuevo;
    }
    cola->contador++;
}

/**
 * @brief Muestra el primer nodo de la bicola.
 *
 * @param cola Puntero a la bicola.
 */
void mostrarPrimerNodo(Bicola* cola) {
    if (!estaVacia(cola)) {
        printf("Archivo: %s\n", cola->inicio->archivo);
    } else {
        printf("La bicola está vacía.\n");
    }
}

/**
 * @brief Muestra todos los nodos de la bicola.
 *
 * @param cola Puntero a la bicola.
 */
void mostrarTodosLosNodos(Bicola* cola) {
    Nodo* actual = cola->inicio;
    while (actual != NULL) {
        printf("%s\n", actual->archivo);
        actual = actual->siguiente;
    }
}

/**
 * @brief Cuenta el número de nodos en la bicola.
 *
 * @param cola Puntero a la bicola.
 * @return int Número de nodos en la bicola.
 */
int contarNodos(Bicola* cola) {
    return cola->contador;
}

/**
 * @brief Elimina el primer nodo de la bicola.
 *
 * @param cola Puntero a la bicola.
 */
void eliminarPrimerNodo(Bicola* cola) {
    if (!estaVacia(cola)) {
        Nodo* aEliminar = cola->inicio;
        cola->inicio = cola->inicio->siguiente;
        free(aEliminar);
        cola->contador--;
        if (cola->inicio == NULL) {
            cola->fin = NULL;
        }
    }
}

/**
 * @brief Elimina todos los nodos de la bicola, dejándola vacía.
 *
 * @param cola Puntero a la bicola.
 */
void eliminarBicola(Bicola* cola) {
    while (!estaVacia(cola)) {
        eliminarPrimerNodo(cola);
    }
}

/**
 * @brief Simula el envío de un archivo, mostrando la primera línea del archivo.
 *
 * @param archivo Nombre del archivo a enviar.
 */
void simularEnvioArchivo(char* archivo) {
    FILE* file = fopen(archivo, "r");
    if (file) {
        char linea[MAX_LINE_LENGTH];
        if (fgets(linea, MAX_LINE_LENGTH, file)) {
            printf("Enviando archivo: %s\n", archivo);
            printf("Primera línea: %s\n", linea);
        } else {
            printf("Archivo vacío o error al leer: %s\n", archivo);
        }
        fclose(file);
    } else {
        printf("No se pudo abrir el archivo: %s\n", archivo);
    }
}

int main() {
    Bicola cola;
    inicializarBicola(&cola);
    char archivo[MAX_LINE_LENGTH];
    int opcion;

    // Menú para ingresar archivos
    do {
        printf("\n1. Ingresar archivo por la derecha\n");
        printf("2. Ingresar archivo por la izquierda\n");
        printf("3. Finalizar ingreso y comenzar envío\n");
        printf("Opción: ");
        scanf("%d", &opcion);
        getchar();  // Limpiar el buffer del teclado

        switch (opcion) {
            case 1:
            case 2:
                printf("Ingrese el nombre del archivo: ");
                fgets(archivo, MAX_LINE_LENGTH, stdin);
                archivo[strcspn(archivo, "\n")] = 0;  // Eliminar el salto de línea

                if (opcion == 1) {
                    ingresarDerecha(&cola, archivo);
                } else {
                    ingresarIzquierda(&cola, archivo);
                }
                break;
            case 3:
                // Finalizar ingreso
                break;
            default:
                printf("Opción no válida.\n");
        }
    } while (opcion != 3);

    // Mostrar cuantos nodos hubo
    int nodos_contados = contarNodos(&cola);
    printf("Hay %d archivos a procesar a modo de nodos \n", nodos_contados);

    // Simulación del envío de archivos
    while (!estaVacia(&cola)) {
        mostrarPrimerNodo(&cola);
        simularEnvioArchivo(cola.inicio->archivo);
        eliminarPrimerNodo(&cola);
        printf("Archivo enviado con éxito.\n");

        // Esperar 3 segundos antes de enviar el siguiente archivo
        sleep(3);
    }

    printf("Nada que enviar. Bicola vacía.\n");
    return 0;
}
