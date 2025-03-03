#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Evitamos el padding de las estructuras
#pragma pack(push, 1)
typedef struct {
    uint16_t bfType;       // Debe ser 'BM' (0x4D42)
    uint32_t bfSize;       // Tamaño total del archivo
    uint16_t bfReserved1;  // Reservado, debe ser 0
    uint16_t bfReserved2;  // Reservado, debe ser 0
    uint32_t bfOffBits;    // Offset hasta los datos de píxeles
} BITMAPFILEHEADER;

typedef struct {
    uint32_t biSize;          // Tamaño de esta cabecera (40 bytes)
    int32_t biWidth;          // Ancho de la imagen
    int32_t biHeight;         // Alto de la imagen
    uint16_t biPlanes;        // Número de planos, siempre 1
    uint16_t biBitCount;      // Bits por píxel (e.g., 24 para imágenes sin compresión)
    uint32_t biCompression;   // Tipo de compresión (0 = sin compresión)
    uint32_t biSizeImage;     // Tamaño de los datos de la imagen (puede ser 0 si no hay compresión)
    int32_t biXPelsPerMeter;  // Resolución horizontal
    int32_t biYPelsPerMeter;  // Resolución vertical
    uint32_t biClrUsed;       // Número de colores usados (0 = todos)
    uint32_t biClrImportant;  // Número de colores importantes
} BITMAPINFOHEADER;
#pragma pack(pop)

// Función para leer un BMP y devolver los datos de píxeles
unsigned char* leerBMP(const char* filename, BITMAPFILEHEADER* fileHeader, BITMAPINFOHEADER* infoHeader) {
    FILE* f = fopen(filename, "rb");
    if (!f) {
        printf("Error al abrir el archivo %s\n", filename);
        return NULL;
    }

    // Leer BITMAPFILEHEADER
    if (fread(fileHeader, sizeof(BITMAPFILEHEADER), 1, f) != 1) {
        printf("Error al leer BITMAPFILEHEADER.\n");
        fclose(f);
        return NULL;
    }

    // Verificar que es un archivo BMP
    if (fileHeader->bfType != 0x4D42) {
        printf("El archivo no es un BMP válido.\n");
        fclose(f);
        return NULL;
    }

    // Leer BITMAPINFOHEADER
    if (fread(infoHeader, sizeof(BITMAPINFOHEADER), 1, f) != 1) {
        printf("Error al leer BITMAPINFOHEADER.\n");
        fclose(f);
        return NULL;
    }

    // Sólo se soportan imágenes de 24 bits sin compresión
    if (infoHeader->biBitCount != 24 || infoHeader->biCompression != 0) {
        printf("Sólo se soportan imágenes de 24 bits sin compresión.\n");
        fclose(f);
        return NULL;
    }

    // Calcular el tamaño de cada fila (con padding: cada fila debe ser múltiplo de 4 bytes)
    int row_padded = (infoHeader->biWidth * 3 + 3) & (~3);
    int dataSize = row_padded * abs(infoHeader->biHeight);

    unsigned char* data = (unsigned char*)malloc(dataSize);
    if (!data) {
        printf("Error al asignar memoria para los datos de la imagen.\n");
        fclose(f);
        return NULL;
    }

    // Mover el puntero del archivo al inicio de los datos de píxeles
    fseek(f, fileHeader->bfOffBits, SEEK_SET);
    if (fread(data, sizeof(unsigned char), dataSize, f) != dataSize) {
        printf("Error al leer los datos de píxeles.\n");
        free(data);
        fclose(f);
        return NULL;
    }

    fclose(f);
    return data;
}

// Función para convertir el valor RGB a luminancia (brillo)
unsigned char calcularLuminancia(unsigned char r, unsigned char g, unsigned char b) {
    return (unsigned char)(0.299 * r + 0.587 * g + 0.114 * b);
}

// Función para mostrar la imagen en arte ASCII
void mostrarASCII(unsigned char* pixelData, BITMAPINFOHEADER infoHeader) {
    // Gradiente de caracteres (de menor a mayor intensidad visual)
    const char* gradiente = " .:-=+*#%@";
    int numNiveles = 10;  // Número de caracteres en el gradiente
    int row_padded = (infoHeader.biWidth * 3 + 3) & (~3);
    int width = infoHeader.biWidth;
    int height = abs(infoHeader.biHeight);

    // Determinar el orden de las filas según la altura (BMP se almacena de abajo hacia arriba si biHeight es positivo)
    int start = (infoHeader.biHeight > 0) ? height - 1 : 0;
    int end = (infoHeader.biHeight > 0) ? -1 : height;
    int step = (infoHeader.biHeight > 0) ? -1 : 1;

    // Recorrer cada píxel y mostrar su equivalente en ASCII
    for (int i = start; i != end; i += step) {
        for (int j = 0; j < width; j++) {
            // Cada píxel tiene 3 bytes (B, G, R)
            int index = i * row_padded + j * 3;
            unsigned char b = pixelData[index];
            unsigned char g = pixelData[index + 1];
            unsigned char r = pixelData[index + 2];
            unsigned char lum = calcularLuminancia(r, g, b);
            // Mapear la luminancia a un índice en el gradiente
            int pos = (lum * (numNiveles - 1)) / 255;
            printf("%c", gradiente[pos]);
        }
        printf("\n");
    }
}

int main() {
    const char* filename = "imagen.bmp";
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;

    unsigned char* pixelData = leerBMP(filename, &fileHeader, &infoHeader);
    if (!pixelData) {
        return 1;
    }

    // Mostrar información básica de la imagen
    printf("Ancho: %d\n", infoHeader.biWidth);
    printf("Alto: %d\n", infoHeader.biHeight);
    printf("Bits por píxel: %d\n", infoHeader.biBitCount);
    printf("\n--- Imagen en ASCII ---\n\n");

    // Mostrar la imagen en ASCII
    mostrarASCII(pixelData, infoHeader);

    // Liberar la memoria reservada
    free(pixelData);
    return 0;
}
