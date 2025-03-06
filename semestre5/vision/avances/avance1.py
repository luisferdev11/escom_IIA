import cv2
import numpy as np
import sys

def detectar_bordes(ruta_imagen):
    # Cargar la imagen
    imagen = cv2.imread(ruta_imagen)
    if imagen is None:
        print("Error: No se pudo cargar la imagen.")
        sys.exit(1)
    
    # Convertir la imagen a escala de grises
    gris = cv2.cvtColor(imagen, cv2.COLOR_BGR2GRAY)
    
    # Aplicar un desenfoque Gaussiano para reducir el ruido
    desenfoque = cv2.GaussianBlur(gris, (5, 5), 0)
    
    # Aplicar el detector de bordes de Canny
    bordes = cv2.Canny(desenfoque, 50, 150)
    
    return imagen, bordes

if __name__ == "__main__":
    # Verificar que se proporcione una ruta de imagen como argumento
    if len(sys.argv) < 2:
        print("Uso: python detectar_bordes.py ruta_de_la_imagen")
        sys.exit(1)
    
    ruta = sys.argv[1]
    imagen_original, imagen_bordes = detectar_bordes(ruta)
    
    # Mostrar la imagen original y la imagen con bordes detectados
    cv2.imshow("Imagen Original", imagen_original)
    cv2.imshow("Bordes Detectados", imagen_bordes)
    
    # Esperar a que se presione una tecla y luego cerrar todas las ventanas
    cv2.waitKey(0)
    cv2.destroyAllWindows()
