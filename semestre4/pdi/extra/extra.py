import cv2
import numpy as np
import tkinter as tk
from tkinter import filedialog, messagebox
from PIL import Image, ImageTk
import os
from tkinter import ttk
from typing import Tuple, Optional, Dict

def preprocesar_imagen_color(img_color: np.ndarray) -> np.ndarray:
    """
    Preprocesa una imagen a color convirtiéndola a escala de grises, binarizándola,
    aplicando filtros de mediana, dilataciones y erosiones.

    Args:
        img_color (np.ndarray): Imagen en color (BGR).

    Returns:
        np.ndarray: Imagen binaria resultante.
    """
    # 1) Convertir a escala de grises
    img_gray = cv2.cvtColor(img_color, cv2.COLOR_BGR2GRAY)

    # 2) Binarizar con umbral fijo
    _, img_bin = cv2.threshold(img_gray, 70, 255, cv2.THRESH_BINARY)

    # 3) Aplicar 2 filtros de mediana
    img_bin = cv2.medianBlur(img_bin, 3)
    img_bin = cv2.medianBlur(img_bin, 3)

    # 4) Aplicar filtro máximo (dilataciones) 5 veces
    kernel = np.ones((3, 3), np.uint8)
    img_bin = cv2.dilate(img_bin, kernel, iterations=5)

    # 5) Aplicar filtro mínimo (erosiones) 14 veces
    img_bin = cv2.erode(img_bin, kernel, iterations=14)

    return img_bin

class MorfologiaGUI:
    def __init__(self, master: tk.Tk) -> None:
        """
        Inicializa la interfaz gráfica de usuario para procesamiento de imágenes.

        Args:
            master (tk.Tk): Instancia principal de Tkinter.
        """
        self.master = master
        self.master.title("Morfología Matemática Binaria y Componentes Conexas")
        self.master.geometry("1800x1000")  # Tamaño ampliado para más imágenes

        # Frame para los botones de control
        frame_botones = tk.Frame(self.master)
        frame_botones.pack(pady=10)

        # Botón para seleccionar imagen
        self.boton_seleccionar = tk.Button(
            frame_botones, text="Seleccionar archivo", command=self.seleccionar_imagen
        )
        self.boton_seleccionar.pack(side="left", padx=5)

        # Casilla de verificación para aplicar preprocesamiento
        self.aplicar_preprocesamiento_var = tk.BooleanVar(value=True)
        self.checkbox_preprocesamiento = tk.Checkbutton(
            frame_botones,
            text="Aplicar Preprocesamiento",
            variable=self.aplicar_preprocesamiento_var
        )
        self.checkbox_preprocesamiento.pack(side="left", padx=5)

        # Botón para invertir colores de la binaria
        self.boton_invertir = tk.Button(
            frame_botones,
            text="Invertir Binaria",
            command=self.invertir_binaria,
            state='disabled'
        )
        self.boton_invertir.pack(side="left", padx=5)

        # Botón para contar manchas
        self.boton_contar = tk.Button(
            frame_botones,
            text="Contar Manchas",
            command=self.contar_manchas,
            state='disabled'
        )
        self.boton_contar.pack(side="left", padx=5)

        # Checkbox para mostrar la imagen sobrepuesta
        self.mostrar_sobrepuesta_var = tk.BooleanVar(value=False)
        self.checkbox_mostrar_sobrepuesta = tk.Checkbutton(
            frame_botones,
            text="Mostrar Imagen Sobrepuesta",
            variable=self.mostrar_sobrepuesta_var,
            command=self.actualizar_sobrepuesta
        )
        self.checkbox_mostrar_sobrepuesta.pack(side="left", padx=5)

        # Opciones para resaltar borde o relleno
        self.tipo_resaltado_var = tk.StringVar(value="Borde")
        frame_resaltado = tk.Frame(frame_botones)
        frame_resaltado.pack(side="left", padx=10)

        tk.Label(frame_resaltado, text="Resaltar:").pack(side="left")
        self.radio_borde = tk.Radiobutton(
            frame_resaltado,
            text="Borde",
            variable=self.tipo_resaltado_var,
            value="Borde",
            command=self.actualizar_sobrepuesta
        )
        self.radio_borde.pack(side="left")

        self.radio_relleno = tk.Radiobutton(
            frame_resaltado,
            text="Relleno",
            variable=self.tipo_resaltado_var,
            value="Relleno",
            command=self.actualizar_sobrepuesta
        )
        self.radio_relleno.pack(side="left")

        # Label para mostrar el directorio actual
        self.directorio_label = tk.Label(
            self.master, text=f"Directorio actual: {os.getcwd()}"
        )
        self.directorio_label.pack(pady=5)

        # Canvas con scrollbar vertical para las imágenes
        self.canvas = tk.Canvas(self.master)
        self.scrollbar = ttk.Scrollbar(self.master, orient="vertical", command=self.canvas.yview)
        self.scrollable_frame = tk.Frame(self.canvas)

        self.scrollable_frame.bind(
            "<Configure>",
            lambda e: self.canvas.configure(scrollregion=self.canvas.bbox("all"))
        )

        self.canvas.create_window((0, 0), window=self.scrollable_frame, anchor="nw")
        self.canvas.configure(yscrollcommand=self.scrollbar.set)

        self.canvas.pack(side="left", fill="both", expand=True)
        self.scrollbar.pack(side="right", fill="y")

        self.frame_imagenes = self.scrollable_frame

        # Kernel para operaciones morfológicas
        self.kernel = np.ones((5, 5), np.uint8)

        # Diccionarios para almacenar imágenes procesadas
        self.imagenes_cv2: Dict[str, np.ndarray] = {}
        self.imagenes_tk: Dict[str, ImageTk.PhotoImage] = {}

        # Flag para indicar si la imagen binaria está invertida
        self.invertida: bool = False

    def seleccionar_imagen(self) -> None:
        """
        Abre un diálogo para seleccionar una imagen, la carga y procesa según la opción seleccionada.
        """
        ruta_imagen = filedialog.askopenfilename(
            title="Seleccionar archivo",
            filetypes=[("Imágenes", "*.png;*.jpg;*.jpeg;*.bmp;*.tiff"), ("Todos los archivos", "*.*")]
        )

        if ruta_imagen and os.path.isfile(ruta_imagen):
            aplicar_preprocesamiento = self.aplicar_preprocesamiento_var.get()

            if aplicar_preprocesamiento:
                # Cargar la imagen a COLOR y aplicar preprocesamiento
                imagen_color = cv2.imread(ruta_imagen)
                if imagen_color is None:
                    messagebox.showerror("Error", "No se pudo cargar el archivo seleccionado como imagen.")
                    return

                # Guardar la imagen original en escala de grises
                imagen_gris = cv2.cvtColor(imagen_color, cv2.COLOR_BGR2GRAY)
                self.imagenes_cv2['original'] = imagen_gris.copy()

                # Habilitar el botón de invertir colores
                self.boton_invertir.config(state='normal', text="Invertir Binaria")
                self.invertida = False  # Resetear flag de inversión

                # Deshabilitar el botón de contar manchas hasta procesar la imagen
                self.boton_contar.config(state='disabled')

                # Procesar la imagen con preprocesamiento
                self.procesar_imagen(imagen_color)
            else:
                # Cargar la imagen como binaria directamente
                imagen_binaria = cv2.imread(ruta_imagen, cv2.IMREAD_GRAYSCALE)
                if imagen_binaria is None:
                    messagebox.showerror("Error", "No se pudo cargar el archivo seleccionado como imagen binaria.")
                    return

                # Asegurarse de que la imagen sea binaria
                _, imagen_binaria = cv2.threshold(imagen_binaria, 127, 255, cv2.THRESH_BINARY)

                self.imagenes_cv2['binaria'] = imagen_binaria.copy()

                # Habilitar el botón de invertir colores
                self.boton_invertir.config(state='normal', text="Invertir Binaria")
                self.invertida = False  # Resetear flag de inversión

                # Procesar la imagen binaria directamente
                self.procesar_imagen_sin_preprocesamiento(imagen_binaria)

            # Resetear opciones de sobreposición
            self.mostrar_sobrepuesta_var.set(False)

    def invertir_binaria(self) -> None:
        """
        Invierte la imagen binaria actual (blanco <-> negro).
        """
        if 'binaria' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen binaria para invertir.")
            return

        if not self.invertida:
            # Invertir la binaria
            bin_invertida = cv2.bitwise_not(self.imagenes_cv2['binaria'])
            self.imagenes_cv2['binaria_invertida'] = bin_invertida
            self.invertida = True
            self.boton_invertir.config(text="Usar Binaria Original")
        else:
            # Volver a la binaria original
            self.invertida = False
            self.boton_invertir.config(text="Invertir Binaria")

        # Actualizar la visualización
        self.mostrar_binaria_actual()

        # Actualizar la imagen sobrepuesta si está activada
        if self.mostrar_sobrepuesta_var.get():
            self.actualizar_sobrepuesta()

    def mostrar_binaria_actual(self) -> None:
        """
        Muestra la imagen binaria actual en la interfaz.
        """
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Aplicar operaciones morfológicas
        apertura = cv2.morphologyEx(bin_actual, cv2.MORPH_OPEN, self.kernel)
        cierre = cv2.morphologyEx(bin_actual, cv2.MORPH_CLOSE, self.kernel)
        self.imagenes_cv2['apertura_binaria'] = apertura
        self.imagenes_cv2['cierre_binaria'] = cierre

        # Análisis de componentes conexas
        num_componentes, etiquetas = self.analizar_componentes_conexas(cierre)
        self.imagenes_cv2['componentes'] = self.colorear_componentes(etiquetas)
        self.imagenes_cv2['num_componentes'] = num_componentes - 1  # Restar 1 si se considera el fondo

        # Mostrar resultados en la interfaz
        self.mostrar_y_actualizar()

        # Habilitar el botón para contar manchas
        self.boton_contar.config(state='normal')

    def procesar_imagen(self, imagen_color: np.ndarray) -> None:
        """
        Procesa la imagen a color realizando preprocesamiento, binarización,
        operaciones morfológicas y análisis de componentes conexas.

        Args:
            imagen_color (np.ndarray): Imagen en color (BGR).
        """
        # Preprocesar a binaria
        imagen_binaria = preprocesar_imagen_color(imagen_color)
        self.imagenes_cv2['binaria'] = imagen_binaria

        # Aplicar apertura y cierre
        apertura = cv2.morphologyEx(imagen_binaria, cv2.MORPH_OPEN, self.kernel)
        cierre = cv2.morphologyEx(imagen_binaria, cv2.MORPH_CLOSE, self.kernel)
        self.imagenes_cv2['apertura_binaria'] = apertura
        self.imagenes_cv2['cierre_binaria'] = cierre

        # Análisis de componentes conexas
        num_componentes, etiquetas = self.analizar_componentes_conexas(cierre)
        self.imagenes_cv2['componentes'] = self.colorear_componentes(etiquetas)
        self.imagenes_cv2['num_componentes'] = num_componentes - 1  # Restar 1 si se considera el fondo

        # Mostrar resultados en la interfaz
        self.mostrar_y_actualizar()

        # Habilitar el botón para contar manchas
        self.boton_contar.config(state='normal')

    def procesar_imagen_sin_preprocesamiento(self, imagen_binaria: np.ndarray) -> None:
        """
        Procesa una imagen binaria directamente para análisis de componentes conexas.

        Args:
            imagen_binaria (np.ndarray): Imagen binaria.
        """
        # Guardar la binaria en el diccionario
        self.imagenes_cv2['binaria'] = imagen_binaria

        # Aplicar apertura y cierre
        apertura = cv2.morphologyEx(imagen_binaria, cv2.MORPH_OPEN, self.kernel)
        cierre = cv2.morphologyEx(imagen_binaria, cv2.MORPH_CLOSE, self.kernel)
        self.imagenes_cv2['apertura_binaria'] = apertura
        self.imagenes_cv2['cierre_binaria'] = cierre

        # Análisis de componentes conexas
        num_componentes, etiquetas = self.analizar_componentes_conexas(cierre)
        self.imagenes_cv2['componentes'] = self.colorear_componentes(etiquetas)
        self.imagenes_cv2['num_componentes'] = num_componentes - 1  # Restar 1 si se considera el fondo

        # Mostrar resultados en la interfaz
        self.mostrar_y_actualizar()

        # Habilitar el botón para contar manchas
        self.boton_contar.config(state='normal')

    def analizar_componentes_conexas(self, imagen_binaria: np.ndarray) -> Tuple[int, np.ndarray]:
        """
        Analiza las componentes conexas de una imagen binaria.

        Args:
            imagen_binaria (np.ndarray): Imagen binaria.

        Returns:
            Tuple[int, np.ndarray]: Número de componentes y etiquetas de cada componente.
        """
        num_componentes, etiquetas = cv2.connectedComponents(imagen_binaria)
        return num_componentes, etiquetas

    def colorear_componentes(self, etiquetas: np.ndarray) -> np.ndarray:
        """
        Asigna un color único a cada componente conexa.

        Args:
            etiquetas (np.ndarray): Mapa de etiquetas de componentes.

        Returns:
            np.ndarray: Imagen coloreada de las componentes.
        """
        if etiquetas.max() == 0:
            # Si no hay componentes, retornar imagen negra
            return np.zeros((etiquetas.shape[0], etiquetas.shape[1], 3), dtype=np.uint8)

        # Crear una imagen HSV donde cada etiqueta tiene un tono único
        label_hue = np.uint8(179 * etiquetas / np.max(etiquetas))
        blank_ch = 255 * np.ones_like(label_hue)
        colored_labels = cv2.merge([label_hue, blank_ch, blank_ch])
        colored_labels = cv2.cvtColor(colored_labels, cv2.COLOR_HSV2BGR)
        colored_labels[label_hue == 0] = 0  # Fondo en negro
        return colored_labels

    def cv2_to_pil(self, img_cv2: np.ndarray, max_size: Tuple[int, int] = (400, 400)) -> Optional[Image.Image]:
        """
        Convierte una imagen de OpenCV a una imagen PIL.

        Args:
            img_cv2 (np.ndarray): Imagen en formato OpenCV.
            max_size (Tuple[int, int], optional): Tamaño máximo de la imagen. Defaults to (400, 400).

        Returns:
            Optional[Image.Image]: Imagen en formato PIL o None si img_cv2 es None.
        """
        if img_cv2 is None:
            return None
        if len(img_cv2.shape) == 2:  # Imagen en escala de grises
            pil_image = Image.fromarray(img_cv2).convert("RGB")
        else:  # Imagen en color
            pil_image = Image.fromarray(cv2.cvtColor(img_cv2, cv2.COLOR_BGR2RGB))
        pil_image.thumbnail(max_size, Image.Resampling.LANCZOS)  # Redimensionar manteniendo relación
        return pil_image

    def mostrar_y_actualizar(self) -> None:
        """
        Convierte las imágenes procesadas a formato PIL y actualiza la interfaz gráfica.
        """
        # Convertir imágenes a formato PIL
        img_original_pil = self.cv2_to_pil(self.imagenes_cv2.get('original'))
        img_binaria_pil = self.cv2_to_pil(self.imagenes_cv2.get('binaria'))
        img_apertura_pil = self.cv2_to_pil(self.imagenes_cv2.get('apertura_binaria'))
        img_cierre_pil = self.cv2_to_pil(self.imagenes_cv2.get('cierre_binaria'))
        img_componentes_pil = self.cv2_to_pil(self.imagenes_cv2.get('componentes'))

        # Mostrar las imágenes en la interfaz
        self.mostrar_resultados(
            img_original=img_original_pil,
            img_binaria=img_binaria_pil,
            img_apertura=img_apertura_pil,
            img_cierre=img_cierre_pil,
            img_componentes=img_componentes_pil
        )

        # Actualizar la imagen sobrepuesta si está activada
        if self.mostrar_sobrepuesta_var.get():
            self.actualizar_sobrepuesta()

    def mostrar_resultados(
        self,
        img_original: Optional[Image.Image],
        img_binaria: Optional[Image.Image],
        img_apertura: Optional[Image.Image],
        img_cierre: Optional[Image.Image],
        img_componentes: Optional[Image.Image]
    ) -> None:
        """
        Muestra las imágenes procesadas en la interfaz gráfica.

        Args:
            img_original (Optional[Image.Image]): Imagen original en escala de grises.
            img_binaria (Optional[Image.Image]): Imagen binaria.
            img_apertura (Optional[Image.Image]): Imagen después de apertura.
            img_cierre (Optional[Image.Image]): Imagen después de cierre.
            img_componentes (Optional[Image.Image]): Imagen de componentes conexas coloreadas.
        """
        # Limpiar el frame de imágenes
        for widget in self.frame_imagenes.winfo_children():
            widget.destroy()

        # Crear filas para cada tipo de imagen
        filas = [tk.Frame(self.frame_imagenes) for _ in range(7)]
        for fila in filas:
            fila.pack(pady=10, anchor="w")

        # Función auxiliar para agregar imagen y etiqueta
        def agregar_imagen_y_etiqueta(frame: tk.Frame, texto: str, imagen_pil: Optional[Image.Image]) -> None:
            tk.Label(frame, text=texto).pack(side="left", padx=10)
            if imagen_pil:
                imagen_tk = ImageTk.PhotoImage(imagen_pil)
                lbl_img = tk.Label(frame, image=imagen_tk)
                lbl_img.image = imagen_tk  # Evita que se recolecte por garbage collector
                lbl_img.pack(side="left", padx=10)

        # Fila 1: Componentes Conexas
        agregar_imagen_y_etiqueta(filas[0], "Componentes Conexas", img_componentes)

        # Fila 2: Original (solo si se aplicó preprocesamiento)
        if 'original' in self.imagenes_cv2:
            agregar_imagen_y_etiqueta(filas[1], "Original (Gris)", img_original)
            fila_inicio = 2
        else:
            fila_inicio = 1

        # Fila 3: Binaria
        agregar_imagen_y_etiqueta(filas[fila_inicio], "Binaria", img_binaria)

        # Fila 4: Apertura
        agregar_imagen_y_etiqueta(filas[fila_inicio + 1], "Apertura", img_apertura)

        # Fila 5: Cierre
        agregar_imagen_y_etiqueta(filas[fila_inicio + 2], "Cierre", img_cierre)

        # Fila 6: Botones para guardar las imágenes procesadas
        self.agregar_botones_guardar(filas[fila_inicio + 3])

        # Fila 7: Imagen Sobrepuesta
        self.label_sobrepuesta = tk.Label(filas[fila_inicio + 4], text="Imagen Sobrepuesta")
        self.label_sobrepuesta.pack(side="left", padx=10)
        self.lbl_img_sobrepuesta = tk.Label(filas[fila_inicio + 4])
        self.lbl_img_sobrepuesta.pack(side="left", padx=10)

    def agregar_botones_guardar(self, fila: tk.Frame) -> None:
        """
        Agrega botones para guardar cada una de las imágenes procesadas.

        Args:
            fila (tk.Frame): Frame donde se agregarán los botones.
        """
        botones_info = [
            ("Guardar Binaria", 'binaria', "binaria.png"),
            ("Guardar Apertura", 'apertura_binaria', "apertura.png"),
            ("Guardar Cierre", 'cierre_binaria', "cierre.png"),
            ("Guardar Componentes", 'componentes', "componentes.png")
        ]

        # Si se aplicó preprocesamiento, agregar opción para guardar la original
        if 'original' in self.imagenes_cv2:
            botones_info.insert(0, ("Guardar Original", 'original', "original.png"))

        # Agregar botón para guardar la imagen sobrepuesta si está activa
        if self.mostrar_sobrepuesta_var.get():
            botones_info.append(("Guardar Sobrepuesta", 'sobrepuesta', "sobrepuesta.png"))

        for texto, clave, filename in botones_info:
            boton = tk.Button(
                fila,
                text=texto,
                command=lambda c=clave, f=filename: self.guardar_imagen(c, f)
            )
            boton.pack(side="left", padx=5)

    def guardar_imagen(self, clave: str, default_filename: str) -> None:
        """
        Guarda la imagen especificada en el disco.

        Args:
            clave (str): Clave de la imagen en el diccionario `imagenes_cv2`.
            default_filename (str): Nombre de archivo por defecto.
        """
        if clave not in self.imagenes_cv2 and clave != 'sobrepuesta':
            messagebox.showerror("Error", f"No hay imagen para guardar: {clave}")
            return

        if clave == 'sobrepuesta' and 'sobrepuesta' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen sobrepuesta para guardar.")
            return

        ruta_guardado = filedialog.asksaveasfilename(
            title="Guardar Imagen",
            defaultextension=".png",
            initialfile=default_filename,
            filetypes=[("PNG", "*.png"), ("JPEG", "*.jpg;*.jpeg"), ("All Files", "*.*")]
        )
        if ruta_guardado:
            if clave == 'sobrepuesta':
                img_a_guardar = self.imagenes_cv2['sobrepuesta']
            else:
                img_a_guardar = self.imagenes_cv2[clave]
            cv2.imwrite(ruta_guardado, img_a_guardar)
            messagebox.showinfo("Guardado", f"Imagen guardada en {ruta_guardado}")

    def contar_manchas(self) -> None:
        """
        Cuenta y muestra el número de manchas detectadas.
        """
        if 'num_componentes' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay componentes detectadas para contar.")
            return
        num_manchas = self.imagenes_cv2['num_componentes']
        messagebox.showinfo("Contar Manchas", f"Se detectaron {num_manchas} manchas.")

    def actualizar_sobrepuesta(self) -> None:
        """
        Actualiza la imagen sobrepuesta según las opciones seleccionadas por el usuario.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            self.mostrar_y_actualizar()
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def actualizar_sobrepuesta(self) -> None:
        """
        Actualiza la imagen sobrepuesta según las opciones seleccionadas por el usuario.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def sobreponer_manchas(self) -> None:
        """
        Sobrepone las manchas detectadas en la imagen original según la opción seleccionada.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def actualizar_sobrepuesta(self) -> None:
        """
        Actualiza la imagen sobrepuesta según las opciones seleccionadas por el usuario.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def sobreponer_manchas(self) -> None:
        """
        Sobrepone las manchas detectadas en la imagen original según la opción seleccionada.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def mostrar_sobrepuesta_actualizada(self) -> None:
        """
        Actualiza y muestra la imagen sobrepuesta en la interfaz.
        """
        if not self.mostrar_sobrepuesta_var.get():
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def mostrar_sobrepuesta_actual(self) -> None:
        """
        Muestra la imagen sobrepuesta en la interfaz gráfica.
        """
        if 'sobrepuesta' not in self.imagenes_cv2:
            self.lbl_img_sobrepuesta.config(image='')
            return

        img_sobrepuesta_pil = self.cv2_to_pil(self.imagenes_cv2['sobrepuesta'])
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def mostrar_sobrepuesta(self) -> None:
        """
        Actualiza y muestra la imagen sobrepuesta en la interfaz.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def actualizar_sobrepuesta(self) -> None:
        """
        Actualiza la imagen sobrepuesta según las opciones seleccionadas por el usuario.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def sobreponer_manchas(self) -> None:
        """
        Sobrepone las manchas detectadas en la imagen original según la opción seleccionada.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def actualizar_sobrepuesta(self) -> None:
        """
        Actualiza la imagen sobrepuesta según las opciones seleccionadas por el usuario.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def mostrar_sobrepuesta_actual(self) -> None:
        """
        Muestra la imagen sobrepuesta en la interfaz gráfica.
        """
        if 'sobrepuesta' not in self.imagenes_cv2:
            self.lbl_img_sobrepuesta.config(image='')
            return

        img_sobrepuesta_pil = self.cv2_to_pil(self.imagenes_cv2['sobrepuesta'])
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

    def mostrar_resultados(
        self,
        img_original: Optional[Image.Image],
        img_binaria: Optional[Image.Image],
        img_apertura: Optional[Image.Image],
        img_cierre: Optional[Image.Image],
        img_componentes: Optional[Image.Image]
    ) -> None:
        """
        Muestra las imágenes procesadas en la interfaz gráfica.

        Args:
            img_original (Optional[Image.Image]): Imagen original en escala de grises.
            img_binaria (Optional[Image.Image]): Imagen binaria.
            img_apertura (Optional[Image.Image]): Imagen después de apertura.
            img_cierre (Optional[Image.Image]): Imagen después de cierre.
            img_componentes (Optional[Image.Image]): Imagen de componentes conexas coloreadas.
        """
        # Limpiar el frame de imágenes
        for widget in self.frame_imagenes.winfo_children():
            widget.destroy()

        # Crear filas para cada tipo de imagen
        filas = [tk.Frame(self.frame_imagenes) for _ in range(7)]
        for fila in filas:
            fila.pack(pady=10, anchor="w")

        # Función auxiliar para agregar imagen y etiqueta
        def agregar_imagen_y_etiqueta(frame: tk.Frame, texto: str, imagen_pil: Optional[Image.Image]) -> None:
            tk.Label(frame, text=texto).pack(side="left", padx=10)
            if imagen_pil:
                imagen_tk = ImageTk.PhotoImage(imagen_pil)
                lbl_img = tk.Label(frame, image=imagen_tk)
                lbl_img.image = imagen_tk  # Evita que se recolecte por garbage collector
                lbl_img.pack(side="left", padx=10)

        # Fila 1: Componentes Conexas
        agregar_imagen_y_etiqueta(filas[0], "Componentes Conexas", img_componentes)

        # Fila 2: Original (solo si se aplicó preprocesamiento)
        if 'original' in self.imagenes_cv2:
            agregar_imagen_y_etiqueta(filas[1], "Original (Gris)", img_original)
            fila_inicio = 2
        else:
            fila_inicio = 1

        # Fila 3: Binaria
        agregar_imagen_y_etiqueta(filas[fila_inicio], "Binaria", img_binaria)

        # Fila 4: Apertura
        agregar_imagen_y_etiqueta(filas[fila_inicio + 1], "Apertura", img_apertura)

        # Fila 5: Cierre
        agregar_imagen_y_etiqueta(filas[fila_inicio + 2], "Cierre", img_cierre)

        # Fila 6: Botones para guardar las imágenes procesadas
        self.agregar_botones_guardar(filas[fila_inicio + 3])

        # Fila 7: Imagen Sobrepuesta
        self.label_sobrepuesta = tk.Label(filas[fila_inicio + 4], text="Imagen Sobrepuesta")
        self.label_sobrepuesta.pack(side="left", padx=10)
        self.lbl_img_sobrepuesta = tk.Label(filas[fila_inicio + 4])
        self.lbl_img_sobrepuesta.pack(side="left", padx=10)

    def agregar_botones_guardar(self, fila: tk.Frame) -> None:
        """
        Agrega botones para guardar cada una de las imágenes procesadas.

        Args:
            fila (tk.Frame): Frame donde se agregarán los botones.
        """
        botones_info = [
            ("Guardar Binaria", 'binaria', "binaria.png"),
            ("Guardar Apertura", 'apertura_binaria', "apertura.png"),
            ("Guardar Cierre", 'cierre_binaria', "cierre.png"),
            ("Guardar Componentes", 'componentes', "componentes.png")
        ]

        # Si se aplicó preprocesamiento, agregar opción para guardar la original
        if 'original' in self.imagenes_cv2:
            botones_info.insert(0, ("Guardar Original", 'original', "original.png"))

        # Agregar botón para guardar la imagen sobrepuesta si está activa
        if self.mostrar_sobrepuesta_var.get():
            botones_info.append(("Guardar Sobrepuesta", 'sobrepuesta', "sobrepuesta.png"))

        for texto, clave, filename in botones_info:
            boton = tk.Button(
                fila,
                text=texto,
                command=lambda c=clave, f=filename: self.guardar_imagen(c, f)
            )
            boton.pack(side="left", padx=5)

    def guardar_imagen(self, clave: str, default_filename: str) -> None:
        """
        Guarda la imagen especificada en el disco.

        Args:
            clave (str): Clave de la imagen en el diccionario `imagenes_cv2`.
            default_filename (str): Nombre de archivo por defecto.
        """
        if clave not in self.imagenes_cv2 and clave != 'sobrepuesta':
            messagebox.showerror("Error", f"No hay imagen para guardar: {clave}")
            return

        if clave == 'sobrepuesta' and 'sobrepuesta' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen sobrepuesta para guardar.")
            return

        ruta_guardado = filedialog.asksaveasfilename(
            title="Guardar Imagen",
            defaultextension=".png",
            initialfile=default_filename,
            filetypes=[("PNG", "*.png"), ("JPEG", "*.jpg;*.jpeg"), ("All Files", "*.*")]
        )
        if ruta_guardado:
            if clave == 'sobrepuesta':
                img_a_guardar = self.imagenes_cv2['sobrepuesta']
            else:
                img_a_guardar = self.imagenes_cv2[clave]
            cv2.imwrite(ruta_guardado, img_a_guardar)
            messagebox.showinfo("Guardado", f"Imagen guardada en {ruta_guardado}")

    def contar_manchas(self) -> None:
        """
        Cuenta y muestra el número de manchas detectadas.
        """
        if 'num_componentes' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay componentes detectadas para contar.")
            return
        num_manchas = self.imagenes_cv2['num_componentes']
        messagebox.showinfo("Contar Manchas", f"Se detectaron {num_manchas} manchas.")

    def actualizar_sobrepuesta(self) -> None:
        """
        Actualiza la imagen sobrepuesta según las opciones seleccionadas por el usuario.
        """
        if not self.mostrar_sobrepuesta_var.get():
            # Si no se desea mostrar la sobrepuesta, limpiar la etiqueta
            self.lbl_img_sobrepuesta.config(image='')
            self.imagenes_cv2.pop('sobrepuesta', None)
            return

        if 'original' not in self.imagenes_cv2:
            messagebox.showerror("Error", "No hay imagen original para sobreponer.")
            self.mostrar_sobrepuesta_var.set(False)
            return

        # Obtener la imagen original en color
        imagen_original_color = cv2.cvtColor(self.imagenes_cv2['original'], cv2.COLOR_GRAY2BGR)

        # Obtener la imagen binaria actual
        bin_actual = self.imagenes_cv2['binaria_invertida'] if self.invertida else self.imagenes_cv2['binaria']

        # Encontrar contornos
        contornos, _ = cv2.findContours(bin_actual, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        # Copiar la imagen original para sobreponer
        sobrepuesta = imagen_original_color.copy()

        # Definir el color para resaltar (rojo)
        color_resaltado = (0, 0, 255)  # Rojo en BGR

        # Definir el grosor de la línea
        grosor = 2

        # Resaltar según la opción seleccionada
        if self.tipo_resaltado_var.get() == "Borde":
            # Dibujar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, grosor)
        elif self.tipo_resaltado_var.get() == "Relleno":
            # Rellenar los contornos
            cv2.drawContours(sobrepuesta, contornos, -1, color_resaltado, thickness=cv2.FILLED)

        # Guardar la imagen sobrepuesta en el diccionario
        self.imagenes_cv2['sobrepuesta'] = sobrepuesta

        # Convertir a PIL y mostrar
        img_sobrepuesta_pil = self.cv2_to_pil(sobrepuesta)
        if img_sobrepuesta_pil:
            imagen_tk = ImageTk.PhotoImage(img_sobrepuesta_pil)
            self.lbl_img_sobrepuesta.config(image=imagen_tk)
            self.lbl_img_sobrepuesta.image = imagen_tk  # Evita que se recolecte por garbage collector

# Ejecutar la aplicación
if __name__ == "__main__":
    root = tk.Tk()
    gui = MorfologiaGUI(root)
    root.mainloop()
