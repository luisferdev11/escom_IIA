#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <limits>

#include "bmp_reader.h"
#include "renderer.h"
#include "color_converter.h"
#include "converter_rgb.h"
#include "converter_hsb.h"
#include "converter_cmyk.h"
#include "converter_lab.h"
#include "converter_xyz.h"

// Adelantamos la declaración de SDL_main
#ifdef main
# undef main
#endif

int solicitarOpcionColor() {
    std::cout << "\nSeleccione el modelo de color para la conversión:\n";
    std::cout << "1. RGB (Original)\n";
    std::cout << "2. HSB\n";
    std::cout << "3. CMYK\n";
    std::cout << "4. Lab\n";
    std::cout << "5. XYZ\n";
    std::cout << "0. Salir\n";
    std::cout << "Ingrese el número de la opción deseada: ";

    int opcion = 0;
    std::cin >> opcion;
    return opcion;
}

int main(int argc, char* argv[]) {
    try {
        std::string filename;
        if (argc > 1) {
            filename = argv[1];
        } else {
            std::cout << "Por favor, ingrese la ruta del archivo BMP: ";
            std::cin >> filename;
            // Limpiar el buffer de entrada después de leer con std::cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        auto bmpImage = BMPReader::read(filename);

        std::cout << "Propiedades de la imagen:\n";
        std::cout << " - Ancho: " << bmpImage->getWidth() << " px\n";
        std::cout << " - Alto: " << bmpImage->getHeight() << " px\n";

        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            throw std::runtime_error(std::string("Error al inicializar SDL: ") + SDL_GetError());
        }

        while (true) {
            int opcion = solicitarOpcionColor();
            if (opcion == 0) {
                std::cout << "Saliendo del programa...\n";
                break;
            }

            std::unique_ptr<IColorConverter> converter;
            switch (opcion) {
                case 1:
                    converter = std::make_unique<ConverterRGB>();
                    break;
                case 2:
                    converter = std::make_unique<ConverterHSB>();
                    break;
                case 3:
                    converter = std::make_unique<ConverterCMYK>();
                    break;
                case 4:
                    converter = std::make_unique<ConverterLab>();
                    break;
                case 5:
                    converter = std::make_unique<ConverterXYZ>();
                    break;
                default:
                    std::cout << "Opción inválida. Intente de nuevo.\n";
                    continue;
            }

            auto convertedImage = converter->convert(*bmpImage);

            Renderer renderer;
            renderer.init(
                convertedImage->getWidth(),
                convertedImage->getHeight(),
                "Visor de BMP (" + converter->name() + ")"
            );
            renderer.render(*convertedImage);
            renderer.waitForClose();
            renderer.close();

            std::cout << "Ventana cerrada. Volviendo al menú principal.\n";
        }

        SDL_Quit();

    } catch (const std::exception& e) {
        std::cerr << "Ocurrió un error: " << e.what() << std::endl;
        // Si SDL fue inicializado, asegúrate de cerrarlo
        if (SDL_WasInit(SDL_INIT_VIDEO)) {
            SDL_Quit();
        }
        return 1;
    }

    return 0;
} 