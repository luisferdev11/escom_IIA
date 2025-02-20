import cv2
import numpy as np
import tkinter as tk
from tkinter import filedialog, messagebox
from PIL import Image, ImageTk
import os
from tkinter import ttk

class MorfologiaGUI:
    def __init__(self, master):
        self.master = master
        self.master.title("Morfología Matemática Binaria")
        self.master.geometry("1200x800")  # Establecer un tamaño inicial adecuado

        frame_botones = tk.Frame(self.master)
        frame_botones.pack(pady=10)

        self.boton_seleccionar = tk.Button(frame_botones, text="Seleccionar archivo", command=self.seleccionar_imagen)
        self.boton_seleccionar.pack()

        # Label para mostrar el directorio actual
        self.directorio_label = tk.Label(self.master, text=f"Directorio actual: {os.getcwd()}")
        self.directorio_label.pack(pady=5)

        # Crear un canvas con scrollbar vertical
        self.canvas = tk.Canvas(self.master)
        self.scrollbar = ttk.Scrollbar(self.master, orient="vertical", command=self.canvas.yview)
        self.scrollable_frame = tk.Frame(self.canvas)

        self.scrollable_frame.bind(
            "<Configure>",
            lambda e: self.canvas.configure(
                scrollregion=self.canvas.bbox("all")
            )
        )

        self.canvas.create_window((0, 0), window=self.scrollable_frame, anchor="nw")
        self.canvas.configure(yscrollcommand=self.scrollbar.set)

        self.canvas.pack(side="left", fill="both", expand=True)
        self.scrollbar.pack(side="right", fill="y")

        self.frame_imagenes = self.scrollable_frame

        # Kernel para las operaciones morfológicas
        self.kernel = np.ones((5,5), np.uint8)

        # Diccionario para almacenar las imágenes procesadas en cv2
        self.imagenes_cv2 = {}

        # Diccionario para almacenar las referencias de ImageTk.PhotoImage
        self.imagenes_tk = {}

    def seleccionar_imagen(self):
        # Permitir seleccionar cualquier tipo de archivo
        ruta_imagen = filedialog.askopenfilename(
            title="Seleccionar archivo", 
            filetypes=[("Todos los archivos", "*.*")]
        )

        if ruta_imagen and os.path.isfile(ruta_imagen):
            # Intentar cargar la imagen en escala de grises
            imagen = cv2.imread(ruta_imagen, cv2.IMREAD_GRAYSCALE)
            if imagen is None:
                messagebox.showerror("Error", "No se pudo cargar el archivo seleccionado como imagen.")
                return

            # Almacenar la imagen original
            self.imagenes_cv2['original'] = imagen

            # Aplicar operaciones morfológicas
            self.imagenes_cv2['erosion'] = cv2.erode(imagen, self.kernel, iterations=1)
            self.imagenes_cv2['dilatacion'] = cv2.dilate(imagen, self.kernel, iterations=1)
            self.imagenes_cv2['apertura'] = cv2.morphologyEx(imagen, cv2.MORPH_OPEN, self.kernel)
            self.imagenes_cv2['cierre'] = cv2.morphologyEx(imagen, cv2.MORPH_CLOSE, self.kernel)

            # Calcular la frontera: diferencia absoluta entre dilatación y erosión
            self.imagenes_cv2['frontera'] = cv2.absdiff(self.imagenes_cv2['dilatacion'], self.imagenes_cv2['erosion'])

            # Aplicar gradiente morfológico
            self.imagenes_cv2['gradiente'] = cv2.morphologyEx(imagen, cv2.MORPH_GRADIENT, self.kernel)

            # Aplicar transformadas Top Hat y Black Hat
            self.imagenes_cv2['top_hat'] = cv2.morphologyEx(imagen, cv2.MORPH_TOPHAT, self.kernel)
            self.imagenes_cv2['black_hat'] = cv2.morphologyEx(imagen, cv2.MORPH_BLACKHAT, self.kernel)

            # Convertir a PIL y redimensionar
            img_original_pil = self.cv2_to_pil(self.imagenes_cv2['original'])
            img_erosion_pil = self.cv2_to_pil(self.imagenes_cv2['erosion'])
            img_dilatacion_pil = self.cv2_to_pil(self.imagenes_cv2['dilatacion'])
            img_apertura_pil = self.cv2_to_pil(self.imagenes_cv2['apertura'])
            img_cierre_pil = self.cv2_to_pil(self.imagenes_cv2['cierre'])
            img_frontera_pil = self.cv2_to_pil(self.imagenes_cv2['frontera'])
            img_gradiente_pil = self.cv2_to_pil(self.imagenes_cv2['gradiente'])
            img_top_hat_pil = self.cv2_to_pil(self.imagenes_cv2['top_hat'])
            img_black_hat_pil = self.cv2_to_pil(self.imagenes_cv2['black_hat'])

            self.mostrar_resultados(img_original_pil, img_erosion_pil, img_dilatacion_pil, 
                                    img_apertura_pil, img_cierre_pil, img_frontera_pil,
                                    img_gradiente_pil, img_top_hat_pil, img_black_hat_pil)

    def cv2_to_pil(self, img_cv2, max_size=(400, 400)):
        pil_image = Image.fromarray(img_cv2)
        pil_image = pil_image.convert("RGB")  # Asegurarse de que esté en modo RGB
        pil_image.thumbnail(max_size, Image.Resampling.LANCZOS)  # Reemplazar ANTIALIAS por Resampling.LANCZOS
        return pil_image

    def mostrar_resultados(self, img_original, img_erosion, img_dilatacion, img_apertura, img_cierre, img_frontera,
                            img_gradiente, img_top_hat, img_black_hat):
        # Limpiar frame de imágenes si ya se mostraron antes
        for widget in self.frame_imagenes.winfo_children():
            widget.destroy()

        # Crear un contenedor vertical para las filas de imágenes
        num_filas = 6  # 5 filas para las imágenes y 1 para los botones de guardar
        filas = []
        for i in range(num_filas):
            fila = tk.Frame(self.frame_imagenes)
            fila.pack(pady=10, anchor="w")
            filas.append(fila)

        # Convertir a ImageTk y almacenar las referencias
        self.imagenes_tk['original'] = ImageTk.PhotoImage(img_original)
        self.imagenes_tk['erosion'] = ImageTk.PhotoImage(img_erosion)
        self.imagenes_tk['dilatacion'] = ImageTk.PhotoImage(img_dilatacion)
        self.imagenes_tk['apertura'] = ImageTk.PhotoImage(img_apertura)
        self.imagenes_tk['cierre'] = ImageTk.PhotoImage(img_cierre)
        self.imagenes_tk['frontera'] = ImageTk.PhotoImage(img_frontera)
        self.imagenes_tk['gradiente'] = ImageTk.PhotoImage(img_gradiente)
        self.imagenes_tk['top_hat'] = ImageTk.PhotoImage(img_top_hat)
        self.imagenes_tk['black_hat'] = ImageTk.PhotoImage(img_black_hat)

        # Fila 1: Original
        frame_fila1 = filas[0]
        label_original = tk.Label(frame_fila1, text="Original")
        label_original.pack(side="left", padx=10)
        lbl_img_original = tk.Label(frame_fila1, image=self.imagenes_tk['original'])
        lbl_img_original.pack(side="left", padx=10)

        # Fila 2: Erosión y Dilatación
        frame_fila2 = filas[1]
        label_erosion = tk.Label(frame_fila2, text="Erosión")
        label_erosion.pack(side="left", padx=10)
        lbl_img_erosion = tk.Label(frame_fila2, image=self.imagenes_tk['erosion'])
        lbl_img_erosion.pack(side="left", padx=10)

        label_dilatacion = tk.Label(frame_fila2, text="Dilatación")
        label_dilatacion.pack(side="left", padx=10)
        lbl_img_dilatacion = tk.Label(frame_fila2, image=self.imagenes_tk['dilatacion'])
        lbl_img_dilatacion.pack(side="left", padx=10)

        # Fila 3: Apertura y Cierre
        frame_fila3 = filas[2]
        label_apertura = tk.Label(frame_fila3, text="Apertura")
        label_apertura.pack(side="left", padx=10)
        lbl_img_apertura = tk.Label(frame_fila3, image=self.imagenes_tk['apertura'])
        lbl_img_apertura.pack(side="left", padx=10)

        label_cierre = tk.Label(frame_fila3, text="Cierre")
        label_cierre.pack(side="left", padx=10)
        lbl_img_cierre = tk.Label(frame_fila3, image=self.imagenes_tk['cierre'])
        lbl_img_cierre.pack(side="left", padx=10)

        # Fila 4: Frontera y Gradiente
        frame_fila4 = filas[3]
        label_frontera = tk.Label(frame_fila4, text="Frontera")
        label_frontera.pack(side="left", padx=10)
        lbl_img_frontera = tk.Label(frame_fila4, image=self.imagenes_tk['frontera'])
        lbl_img_frontera.pack(side="left", padx=10)

        label_gradiente = tk.Label(frame_fila4, text="Gradiente Morfológico")
        label_gradiente.pack(side="left", padx=10)
        lbl_img_gradiente = tk.Label(frame_fila4, image=self.imagenes_tk['gradiente'])
        lbl_img_gradiente.pack(side="left", padx=10)

        # Fila 5: Top Hat y Black Hat
        frame_fila5 = filas[4]
        label_top_hat = tk.Label(frame_fila5, text="Transformada Top Hat")
        label_top_hat.pack(side="left", padx=10)
        lbl_img_top_hat = tk.Label(frame_fila5, image=self.imagenes_tk['top_hat'])
        lbl_img_top_hat.pack(side="left", padx=10)

        label_black_hat = tk.Label(frame_fila5, text="Transformada Black Hat")
        label_black_hat.pack(side="left", padx=10)
        lbl_img_black_hat = tk.Label(frame_fila5, image=self.imagenes_tk['black_hat'])
        lbl_img_black_hat.pack(side="left", padx=10)

        # Fila 6: Botones para guardar imágenes
        self.agregar_botones_guardar(filas[5])

    def agregar_botones_guardar(self, fila):
        # Crear botones para guardar cada imagen procesada
        boton_guardar_original = tk.Button(fila, text="Guardar Original", 
                                          command=lambda: self.guardar_imagen(self.imagenes_cv2['original'], "original.png"))
        boton_guardar_original.pack(side="left", padx=10)

        boton_guardar_erosion = tk.Button(fila, text="Guardar Erosión", 
                                         command=lambda: self.guardar_imagen(self.imagenes_cv2['erosion'], "erosion.png"))
        boton_guardar_erosion.pack(side="left", padx=10)

        boton_guardar_dilatacion = tk.Button(fila, text="Guardar Dilatación", 
                                            command=lambda: self.guardar_imagen(self.imagenes_cv2['dilatacion'], "dilatacion.png"))
        boton_guardar_dilatacion.pack(side="left", padx=10)

        boton_guardar_apertura = tk.Button(fila, text="Guardar Apertura", 
                                          command=lambda: self.guardar_imagen(self.imagenes_cv2['apertura'], "apertura.png"))
        boton_guardar_apertura.pack(side="left", padx=10)

        boton_guardar_cierre = tk.Button(fila, text="Guardar Cierre", 
                                        command=lambda: self.guardar_imagen(self.imagenes_cv2['cierre'], "cierre.png"))
        boton_guardar_cierre.pack(side="left", padx=10)

        boton_guardar_frontera = tk.Button(fila, text="Guardar Frontera", 
                                          command=lambda: self.guardar_imagen(self.imagenes_cv2['frontera'], "frontera.png"))
        boton_guardar_frontera.pack(side="left", padx=10)

        boton_guardar_gradiente = tk.Button(fila, text="Guardar Gradiente", 
                                           command=lambda: self.guardar_imagen(self.imagenes_cv2['gradiente'], "gradiente.png"))
        boton_guardar_gradiente.pack(side="left", padx=10)

        boton_guardar_top_hat = tk.Button(fila, text="Guardar Top Hat", 
                                         command=lambda: self.guardar_imagen(self.imagenes_cv2['top_hat'], "top_hat.png"))
        boton_guardar_top_hat.pack(side="left", padx=10)

        boton_guardar_black_hat = tk.Button(fila, text="Guardar Black Hat", 
                                           command=lambda: self.guardar_imagen(self.imagenes_cv2['black_hat'], "black_hat.png"))
        boton_guardar_black_hat.pack(side="left", padx=10)

    def guardar_imagen(self, img_cv2, default_filename):
        ruta_guardado = filedialog.asksaveasfilename(
            title="Guardar Imagen",
            defaultextension=".png",
            initialfile=default_filename,
            filetypes=[("PNG", "*.png"), ("JPEG", "*.jpg;*.jpeg"), ("All Files", "*.*")]
        )
        if ruta_guardado:
            # Guardar la imagen utilizando OpenCV
            cv2.imwrite(ruta_guardado, img_cv2)
            messagebox.showinfo("Guardado", f"Imagen guardada en {ruta_guardado}")

    def cv2_to_pil(self, img_cv2, max_size=(400, 400)):
        pil_image = Image.fromarray(img_cv2)
        pil_image = pil_image.convert("RGB")  # Asegurarse de que esté en modo RGB
        pil_image.thumbnail(max_size, Image.Resampling.LANCZOS)  # Reemplazar ANTIALIAS por Resampling.LANCZOS
        return pil_image

if __name__ == "__main__":
    root = tk.Tk()
    gui = MorfologiaGUI(root)
    root.mainloop()
