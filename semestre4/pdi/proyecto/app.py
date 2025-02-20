import cv2
import numpy as np
import tkinter as tk
from tkinter import Menu
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.pyplot as plt

# --- Cargar un clasificador Haar para detección facial ---
detector_rostro = cv2.CascadeClassifier(cv2.data.haarcascades + "haarcascade_frontalface_default.xml")

def segmentacion_total_otsu():
    global imagen_modificada
    if imagen_modificada is None:
        print("No hay ninguna imagen cargada o modificada.")
        return

    try:
        # Convertir la imagen a escala de grises
        gris = cv2.cvtColor(imagen_modificada, cv2.COLOR_BGR2GRAY)

        # Aplicar un filtro Gaussiano para suavizar la imagen y reducir ruido
        gris_suavizado = cv2.GaussianBlur(gris, (5, 5), 0)

        # Aplicar Umbral de Otsu
        # ret es el umbral encontrado, binaria es la imagen binarizada
        ret, binaria = cv2.threshold(gris_suavizado, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU)

        # Mostrar el resultado (imagen binaria) en la sección de imagen modificada
        mostrar_imagen_histograma(binaria, ax_imagen_modificada, ax_histograma_modificado, f'Segmentación Otsu (Umbral: {ret})')
        canvas.draw()
        ventana.update()
        
        # Para mantener solo las partes blancas de la máscara:
        # Nota: Esto asume que la máscara binaria define la región de interés.
        imagen_segmentada = cv2.bitwise_and(imagen_modificada, imagen_modificada, mask=binaria)

        # Mostramos la imagen segmentada a color (sobre fondo negro donde no hay objeto)
        mostrar_imagen_histograma(imagen_segmentada, ax_imagen_modificada, ax_histograma_modificado, 'Imagen Segmentada con Otsu')
        canvas.draw()
        ventana.update()

        # Actualizamos la imagen modificada con el resultado final (opcional)
        imagen_modificada = imagen_segmentada

    except Exception as e:
        print(f"Error al aplicar la segmentación total con Otsu: {e}")


# --- Función para mostrar la imagen y su histograma ---
def mostrar_imagen_histograma(imagen, ax_imagen, ax_histograma, titulo):
    if len(imagen.shape) == 2:  # Escala de grises
        ax_imagen.imshow(imagen, cmap='gray')
    else:  # Imagen en color
        ax_imagen.imshow(cv2.cvtColor(imagen, cv2.COLOR_BGR2RGB))
    ax_imagen.set_title(titulo)
    ax_imagen.axis('off')
    ax_histograma.clear()
    ax_histograma.hist(imagen.ravel(), 256, [0, 256])  # Generar histograma de la imagen
    ax_histograma.set_title('Histograma')

# --- Función para cargar una imagen ---
def cargar_imagen():
    global imagen_original, imagen_modificada
    ruta_imagen = tk.filedialog.askopenfilename()  # Abrir diálogo para seleccionar imagen
    if ruta_imagen:
        imagen_original = cv2.imread(ruta_imagen)  # Cargar la imagen
        imagen_modificada = imagen_original.copy()  # Crear una copia para modificaciones
        mostrar_imagen_histograma(imagen_original, ax_imagen_original, ax_histograma_original, 'Imagen Original')
        actualizar_imagen_modificada()

# --- Función para reiniciar la imagen a su estado original ---
def reiniciar_imagen():
    global imagen_modificada
    if imagen_original is not None:
        imagen_modificada = imagen_original.copy()
        actualizar_imagen_modificada()

# --- Actualizar la visualización de la imagen modificada ---
def actualizar_imagen_modificada():
    mostrar_imagen_histograma(imagen_modificada, ax_imagen_modificada, ax_histograma_modificado, 'Imagen Modificada')
    canvas.draw()
    ventana.update()  # Forzar actualización de la interfaz gráfica

# --- Segmentación Parcial ---
def segmentacion_parcial_progresiva():
    global imagen_modificada
    if imagen_modificada is None:
        print("No hay ninguna imagen cargada o modificada.")
        return

    try:
        # Paso 1: Detección de Rostro
        imagen_grises = cv2.cvtColor(imagen_modificada, cv2.COLOR_BGR2GRAY)
        rostros = detector_rostro.detectMultiScale(imagen_grises, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

        if len(rostros) == 0:
            print("No se detectaron rostros.")
            return

        # Procesar el primer rostro detectado
        x, y, w, h = rostros[0]
        # Ampliar los bordes del recorte
        margen_x = int(0.05 * w)  # 5% del ancho
        margen_y = int(0.05 * h)  # 5% de la altura

        # Asegurarse de no salir de los límites de la imagen
        inicio_x = max(x - margen_x, 0)
        inicio_y = max(y - margen_y, 0)
        fin_x = min(x + w + margen_x, imagen_modificada.shape[1])
        fin_y = min(y + h + margen_y, imagen_modificada.shape[0])

        rostro = imagen_modificada[inicio_y:fin_y, inicio_x:fin_x]

        # Paso 2: Mostrar el rostro detectado sin zoom
        mostrar_imagen_histograma(imagen_modificada, ax_imagen_modificada, ax_histograma_modificado, 'Rostro Detectado')
        canvas.draw()
        ventana.update()
        ventana.after(1000)

        # Paso 3: Escala de Grises en el Rostro
        rostro_grises = cv2.cvtColor(rostro, cv2.COLOR_BGR2GRAY)
        mostrar_imagen_histograma(rostro_grises, ax_imagen_modificada, ax_histograma_modificado, 'Escala de Grises (Rostro)')
        canvas.draw()
        ventana.update()
        ventana.after(1000)

        # Paso 4: Filtro Gaussiano en el Rostro
        rostro_suavizado = cv2.GaussianBlur(rostro_grises, (5, 5), 0)
        mostrar_imagen_histograma(rostro_suavizado, ax_imagen_modificada, ax_histograma_modificado, 'Filtro Gaussiano (Rostro)')
        canvas.draw()
        ventana.update()
        ventana.after(1000)

        # Paso 5: Bordes con Canny en el Rostro
        rostro_bordes = cv2.Canny(rostro_suavizado, 50, 150)
        mostrar_imagen_histograma(rostro_bordes, ax_imagen_modificada, ax_histograma_modificado, 'Bordes (Canny) del Rostro')
        canvas.draw()
        ventana.update()

        # Actualizar la imagen modificada
        imagen_modificada = rostro_bordes
    except Exception as e:
        print(f"Error al aplicar la segmentación parcial: {e}")

# --- Segmentación Completa ---
def segmentacion_completa():
    global imagen_modificada
    if imagen_modificada is None:
        print("No hay ninguna imagen cargada o modificada.")
        return

    try:
        # Paso 1: Detección de Rostro
        imagen_grises = cv2.cvtColor(imagen_modificada, cv2.COLOR_BGR2GRAY)
        rostros = detector_rostro.detectMultiScale(imagen_grises, scaleFactor=1.1, minNeighbors=5, minSize=(30, 30))

        if len(rostros) == 0:
            print("No se detectaron rostros.")
            return

        # Procesar el primer rostro detectado
        x, y, w, h = rostros[0]
        # Crear una máscara para el rostro
        mascara = np.zeros_like(imagen_grises)
        cv2.rectangle(mascara, (x, y), (x + w, y + h), 255, -1)

        # Operación lógica AND para mantener solo el rostro
        rostro = cv2.bitwise_and(imagen_modificada, imagen_modificada, mask=mascara)

        # Dibujar contorno en el rostro
        cv2.rectangle(rostro, (x, y), (x + w, y + h), (0, 255, 0), 2)

        # Mostrar el resultado
        mostrar_imagen_histograma(rostro, ax_imagen_modificada, ax_histograma_modificado, 'Rostro con Contorno')
        canvas.draw()
        ventana.update()

        # Actualizar la imagen modificada
        imagen_modificada = rostro
    except Exception as e:
        print(f"Error al aplicar la segmentación completa: {e}")

# --- Tratamiento de Ruido Gaussiano Progresivo ---
def tratamiento_ruido_gaussiano():
    global imagen_modificada
    if imagen_modificada is None:
        print("No hay ninguna imagen cargada o modificada.")
        return

    try:
        # Paso 1: Filtro Promediador Pesado
        kernel = np.array([[1, 2, 1],
                           [2, 4, 2],
                           [1, 2, 1]], np.float32) / 16
        imagen_promediada = cv2.filter2D(imagen_modificada, -1, kernel)
        mostrar_imagen_histograma(imagen_promediada, ax_imagen_modificada, ax_histograma_modificado, 'Filtro Promediador Pesado')
        canvas.draw()
        ventana.update()
        ventana.after(1000)

        # Paso 2: Filtro Gaussiano
        imagen_gaussiana = cv2.GaussianBlur(imagen_promediada, (5, 5), 0)
        mostrar_imagen_histograma(imagen_gaussiana, ax_imagen_modificada, ax_histograma_modificado, 'Filtro Gaussiano')
        canvas.draw()
        ventana.update()

        # Actualizar la imagen modificada con el resultado final
        imagen_modificada = imagen_gaussiana
    except Exception as e:
        print(f"Error al aplicar el tratamiento de ruido gaussiano: {e}")

# --- Tratamiento de ruido Sal y Pimienta ---
def aplicar_filtro_mediana():
    global imagen_modificada
    if imagen_modificada is None:
        print("No hay ninguna imagen cargada o modificada.")
        return

    try:
        imagen_modificada = cv2.medianBlur(imagen_modificada, 3)
        actualizar_imagen_modificada()
    except Exception as e:
        print(f"Error al aplicar el filtro de mediana: {e}")

# --- Configuración de la Interfaz Gráfica ---
ventana = tk.Tk()
ventana.title("Editor de Imágenes")
ventana.geometry("800x600")

# Crear barra de menú en la ventana
menu_bar = Menu(ventana)
ventana.config(menu=menu_bar)

# Menú Archivo
archivo_menu = Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label="Archivo", menu=archivo_menu)
archivo_menu.add_command(label="Cargar Imagen", command=cargar_imagen)
archivo_menu.add_command(label="Reiniciar Imagen", command=reiniciar_imagen)
archivo_menu.add_command(label="Salir", command=ventana.quit)

# Menú Operaciones
operaciones_menu = Menu(menu_bar, tearoff=0)
menu_bar.add_cascade(label="Operaciones", menu=operaciones_menu)

# Submenú Segmentación
segmentacion_menu = Menu(operaciones_menu, tearoff=0)
operaciones_menu.add_cascade(label="Segmentación", menu=segmentacion_menu)
segmentacion_menu.add_command(label="Aplicar Segmentación Parcial", command=segmentacion_parcial_progresiva)
segmentacion_menu.add_command(label="Aplicar Segmentación Completa", command=segmentacion_completa)
segmentacion_menu.add_command(label="Segmentación Total con Otsu", command=segmentacion_total_otsu)


# Submenú Tratamiento de Ruido
ruido_menu = Menu(operaciones_menu, tearoff=0)
operaciones_menu.add_cascade(label="Tratamiento de Ruido", menu=ruido_menu)
ruido_menu.add_command(label="Tratamiento de Ruido Gaussiano", command=tratamiento_ruido_gaussiano)
ruido_menu.add_command(label="Tratamiento de Ruido Sal Y Pimienta", command=aplicar_filtro_mediana)

# Crear figura para mostrar imágenes y sus histogramas
fig, axes = plt.subplots(2, 2, figsize=(10, 6))
(ax_imagen_original, ax_histograma_original), (ax_imagen_modificada, ax_histograma_modificado) = axes
plt.subplots_adjust(left=0.05, right=0.95, top=0.95, bottom=0.05, wspace=0.3, hspace=0.4)

# Integrar la figura en la ventana de Tkinter usando FigureCanvasTkAgg
canvas = FigureCanvasTkAgg(fig, master=ventana)
canvas.draw()
canvas.get_tk_widget().pack(side='top', fill='both', expand=1)

# Variables globales para almacenar las imágenes original y modificada
imagen_original = None
imagen_modificada = None

# Iniciar el bucle principal de la interfaz
ventana.mainloop()
