import numpy as np
import matplotlib.pyplot as plt
import cv2
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas

class SignalPlotter:
    """
    Gestiona la creación y actualización de un gráfico de señales en tiempo real
    y lo convierte en una imagen de OpenCV.
    """
    def __init__(self, ref_signal, width=640, height=480, signal_name="Y-Coordinate", landmark_name="Right Wrist"):
        """
        Inicializa el gráfico.

        Args:
            ref_signal (np.array): La señal de referencia completa para graficar.
            width (int): Ancho de la imagen de salida del gráfico.
            height (int): Alto de la imagen de salida del gráfico.
            signal_name (str): Nombre de la señal para el eje Y.
            landmark_name (str): Nombre del landmark para el título.
        """
        self.width = width
        self.height = height
        self.ref_signal = ref_signal
        
        # Historial para la señal en tiempo real
        self.realtime_signal = []

        # Configuración de Matplotlib
        self.fig, self.ax = plt.subplots(figsize=(width / 100, height / 100), dpi=100)
        self.ax.plot(self.ref_signal, label='Referencia', color='blue', linewidth=2)
        self.line, = self.ax.plot(self.realtime_signal, label='Usuario', color='red', linewidth=2)

        # Estilo del gráfico
        self.ax.set_title(f"Señal de {landmark_name}")
        self.ax.set_xlabel("Tiempo (Fotogramas)")
        self.ax.set_ylabel(signal_name)
        self.ax.legend()
        self.ax.grid(True)
        self.ax.set_xlim(0, len(self.ref_signal)) # Eje X fijo
        # Ajustar los límites del eje Y para que coincidan con la señal de referencia
        min_y = np.nanmin(ref_signal)
        max_y = np.nanmax(ref_signal)
        padding = (max_y - min_y) * 0.1
        self.ax.set_ylim(min_y - padding, max_y + padding)
        
        self.fig.tight_layout(pad=2.0)
        self.canvas = FigureCanvas(self.fig)

    def update(self, new_value):
        """
        Añade un nuevo punto de datos a la señal en tiempo real y redibuja el gráfico.

        Args:
            new_value (float): El nuevo valor de la señal del usuario.
        """
        self.realtime_signal.append(new_value)
        self.line.set_data(range(len(self.realtime_signal)), self.realtime_signal)
        return self.get_plot_image()

    def get_plot_image(self):
        """
        Convierte el lienzo actual de Matplotlib en una imagen de OpenCV.

        Returns:
            np.array: La imagen del gráfico en formato BGR.
        """
        self.canvas.draw()
        # Convertir el canvas a un array de RGBA
        s, (width, height) = self.canvas.print_to_buffer()
        rgba_image = np.frombuffer(s, np.uint8).reshape((height, width, 4))
        
        # Convertir de RGBA a BGR para OpenCV
        bgr_image = cv2.cvtColor(rgba_image, cv2.COLOR_RGBA2BGR)
        return bgr_image 