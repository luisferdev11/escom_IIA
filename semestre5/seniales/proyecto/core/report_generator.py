import matplotlib.pyplot as plt
import numpy as np
import mediapipe as mp
import os
import datetime

from .signal_processing import apply_ema

# Usamos el enum de MediaPipe para claridad y mantenibilidad
mp_pose = mp.solutions.pose

# 1. Definir los landmarks de interés
LANDMARKS_TO_REPORT = {
    'ARMS': [
        mp_pose.PoseLandmark.LEFT_SHOULDER, mp_pose.PoseLandmark.RIGHT_SHOULDER,
        mp_pose.PoseLandmark.LEFT_ELBOW, mp_pose.PoseLandmark.RIGHT_ELBOW,
        mp_pose.PoseLandmark.LEFT_WRIST, mp_pose.PoseLandmark.RIGHT_WRIST,
    ],
    'LEGS': [
        mp_pose.PoseLandmark.LEFT_HIP, mp_pose.PoseLandmark.RIGHT_HIP,
        mp_pose.PoseLandmark.LEFT_KNEE, mp_pose.PoseLandmark.RIGHT_KNEE,
        mp_pose.PoseLandmark.LEFT_ANKLE, mp_pose.PoseLandmark.RIGHT_ANKLE,
    ]
}

def get_signal_from_landmark(full_data, landmark_index, coordinate_index):
    """Extrae una señal específica (ej. coord 'X' del codo) de un set de datos completo."""
    # El vector normalizado tiene 3 valores (x,y,z) por landmark.
    vector_index = (landmark_index * 3) + coordinate_index
    signal = []
    for frame_data in full_data:
        if frame_data is not None and len(frame_data) > vector_index:
            signal.append(frame_data[vector_index])
        else:
            signal.append(np.nan) # Usar NaN si no hay datos para ese frame
    return signal

def generate_report(ref_data, user_data, output_filename):
    """
    Genera y guarda un reporte gráfico comparando las señales de pose.
    """
    print("Generando reporte post-sesión...")
    
    # Recopilar todos los landmarks en una sola lista para iterar
    all_landmarks = LANDMARKS_TO_REPORT['ARMS'] + LANDMARKS_TO_REPORT['LEGS']
    num_landmarks = len(all_landmarks)
    
    # Crear una figura con una cuadrícula de subplots. 3 columnas (X, Y, Z)
    fig, axes = plt.subplots(
        nrows=num_landmarks, 
        ncols=3, 
        figsize=(20, 5 * num_landmarks),
        sharex=True # Compartir el eje X (tiempo)
    )
    fig.suptitle('Reporte Comparativo de Movimiento', fontsize=24, y=0.99)

    # Asegurarse de que user_data no sea más largo que ref_data
    min_len = min(len(ref_data), len(user_data))
    ref_data = ref_data[:min_len]
    user_data = user_data[:min_len]

    for i, landmark in enumerate(all_landmarks):
        for j, coord_name in enumerate(['X', 'Y', 'Z']):
            ax = axes[i, j]
            
            # Extraer las señales para este landmark y coordenada
            ref_signal = get_signal_from_landmark(ref_data, landmark.value, j)
            user_signal = get_signal_from_landmark(user_data, landmark.value, j)
            
            # Graficar ambas señales
            ax.plot(ref_signal, 'b-', label='Referencia')
            ax.plot(user_signal, 'r--', label='Usuario')
            
            # Estilo del subplot
            ax.set_title(f'{landmark.name} - Eje {coord_name}')
            ax.grid(True)
            ax.legend()

    plt.tight_layout(rect=[0, 0, 1, 0.98]) # Ajustar layout para el supertítulo
    
    # Guardar la figura
    plt.savefig(output_filename)
    print(f"Reporte guardado exitosamente en '{output_filename}'")
    plt.close(fig) # Cerrar la figura para liberar memoria 

class ReportGenerator:
    """
    Genera un reporte detallado en Markdown con gráficos de análisis de movimiento
    y métricas de rendimiento clave.
    """
    def __init__(self, ref_data, user_data_session):
        self.ref_data = ref_data
        self.user_data_session = user_data_session
        self.report_dir = self._create_report_directory()

        # Asegurar que los datos tengan la misma longitud para la comparación
        min_len = min(len(self.ref_data), len(self.user_data_session))
        self.ref_data = self.ref_data[:min_len]
        self.user_data_session = self.user_data_session[:min_len]

        self.user_pose_vectors = [d['pose_vec'] for d in self.user_data_session]
        self.precision_signal = [d['precision'] for d in self.user_data_session]
        self.overall_scores = [d['overall'] for d in self.user_data_session]

        # Articulaciones de interés para los gráficos
        self.landmarks_to_plot = {
            "WRIST": [mp_pose.PoseLandmark.LEFT_WRIST, mp_pose.PoseLandmark.RIGHT_WRIST],
            "HIP": [mp_pose.PoseLandmark.LEFT_HIP, mp_pose.PoseLandmark.RIGHT_HIP],
            "ANKLE": [mp_pose.PoseLandmark.LEFT_ANKLE, mp_pose.PoseLandmark.RIGHT_ANKLE],
            "KNEE": [mp_pose.PoseLandmark.LEFT_KNEE, mp_pose.PoseLandmark.RIGHT_KNEE],
        }

    def _create_report_directory(self):
        """Crea un directorio único para el reporte basado en la fecha y hora."""
        base_dir = "reports"
        timestamp = datetime.datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        report_dir = os.path.join(base_dir, timestamp)
        os.makedirs(report_dir, exist_ok=True)
        print(f"Directorio del reporte creado en: {report_dir}")
        return report_dir

    def _get_signal(self, data, landmark, coord_idx):
        """Extrae una señal de una lista de vectores de pose."""
        idx = landmark.value * 3 + coord_idx
        return [vec[idx] if vec is not None else np.nan for vec in data]

    def _plot_and_save(self, title, filename, *signals):
        """Función genérica para crear y guardar un gráfico."""
        plt.figure(figsize=(12, 6))
        for label, signal_data, style, alpha_val in signals:
            plt.plot(signal_data, style, label=label, alpha=alpha_val)
        plt.title(title, fontsize=16)
        plt.xlabel("Tiempo (Fotogramas)")
        plt.ylabel("Coordenada Normalizada / Puntuación")
        plt.legend()
        plt.grid(True)
        plt.savefig(os.path.join(self.report_dir, filename))
        plt.close()

    def _calculate_metrics(self):
        """Calcula las métricas de rendimiento clave usando señales suavizadas."""
        metrics = {}
        # Usar la señal de precisión suavizada para el promedio
        smoothed_precision = apply_ema(self.precision_signal, alpha=0.05)
        metrics['avg_score'] = np.nanmean(apply_ema(self.overall_scores, alpha=0.05))
        metrics['avg_precision'] = np.nanmean(smoothed_precision)
        metrics['consistency'] = np.nanstd(smoothed_precision)

        # Análisis por articulación sobre datos suavizados
        landmark_precisions = {}
        all_landmarks_of_interest = [lm for group in self.landmarks_to_plot.values() for lm in group]
        
        for landmark in all_landmarks_of_interest:
            ref_x_raw = self._get_signal(self.ref_data, landmark, 0)
            user_x_raw = self._get_signal(self.user_pose_vectors, landmark, 0)
            
            # Suavizar antes de calcular el error
            ref_x_ema = apply_ema(ref_x_raw)
            user_x_ema = apply_ema(user_x_raw)

            error = np.nanmean(np.abs(ref_x_ema - user_x_ema))
            landmark_precisions[landmark.name] = 1 - error # 1 - error para que más alto sea mejor
        
        if landmark_precisions:
            metrics['best_part'] = max(landmark_precisions, key=landmark_precisions.get)
            metrics['worst_part'] = min(landmark_precisions, key=landmark_precisions.get)
        
        return metrics

    def generate(self):
        """Orquesta la generación de todos los gráficos y el archivo Markdown."""
        print("Generando reporte...")
        image_paths = {}
        ema_alpha = 0.2 # Factor de suavizado para los gráficos

        # 1. Generar gráficos de comparación de articulaciones
        for name, landmarks in self.landmarks_to_plot.items():
            for landmark in landmarks:
                for i, coord in enumerate(['X', 'Y']):
                    ref_signal_raw = self._get_signal(self.ref_data, landmark, i)
                    user_signal_raw = self._get_signal(self.user_pose_vectors, landmark, i)
                    
                    ref_signal_ema = apply_ema(ref_signal_raw, alpha=ema_alpha)
                    user_signal_ema = apply_ema(user_signal_raw, alpha=ema_alpha)

                    title = f"Comparación (Raw vs. EMA) - {landmark.name} - Eje {coord}"
                    filename = f"{landmark.name}_{coord}.png"
                    
                    self._plot_and_save(
                        title, filename, 
                        ('Referencia (Raw)', ref_signal_raw, 'b-', 0.3), 
                        ('Usuario (Raw)', user_signal_raw, 'r-', 0.3),
                        ('Referencia (EMA)', ref_signal_ema, 'b-', 1.0), 
                        ('Usuario (EMA)', user_signal_ema, 'r-', 1.0)
                    )
                    image_paths[f"{landmark.name}_{coord}"] = filename

        # 2. Generar gráfico de precisión
        precision_raw = self.precision_signal
        precision_ema = apply_ema(precision_raw, alpha=0.05)
        title = "Precisión a lo largo del Tiempo (Raw vs. EMA)"
        filename = "precision_over_time.png"
        self._plot_and_save(
            title, filename, 
            ('Precisión (Raw)', precision_raw, 'g-', 0.4),
            ('Precisión (EMA)', precision_ema, 'g-', 1.0)
        )
        image_paths['precision'] = filename

        # 3. Calcular métricas
        metrics = self._calculate_metrics()

        # 4. Construir el archivo Markdown
        md_content = f"""
# Reporte de Sesión de Baile

**Fecha y Hora:** {datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")}

---

## Resumen de Rendimiento

| Métrica | Valor |
|---|---|
| **Puntuación Media General** | **{metrics.get('avg_score', 0):.2f} %** |
| Precisión Media | {metrics.get('avg_precision', 0):.2f} % |
| Consistencia (Desv. Est.) | {metrics.get('consistency', 0):.2f} |
| **Mejor Articulación** | `{metrics.get('best_part', 'N/A')}` |
| **Articulación a Mejorar** | `{metrics.get('worst_part', 'N/A')}` |

---

## Análisis Detallado

### Precisión General de la Sesión (con filtro EMA)
![Precisión a lo largo del tiempo]({image_paths['precision']})

### Desglose por Articulación (Ejes X, Y) - Raw vs. EMA
Las líneas tenues representan los datos en crudo, mientras que las líneas sólidas y opacas muestran la tendencia suavizada con el filtro EMA.

#### Muñecas (Wrists)
![LEFT_WRIST_X]({image_paths['LEFT_WRIST_X']})
![LEFT_WRIST_Y]({image_paths['LEFT_WRIST_Y']})
![RIGHT_WRIST_X]({image_paths['RIGHT_WRIST_X']})
![RIGHT_WRIST_Y]({image_paths['RIGHT_WRIST_Y']})

#### Caderas (Hips)
![LEFT_HIP_X]({image_paths['LEFT_HIP_X']})
![LEFT_HIP_Y]({image_paths['LEFT_HIP_Y']})
![RIGHT_HIP_X]({image_paths['RIGHT_HIP_X']})
![RIGHT_HIP_Y]({image_paths['RIGHT_HIP_Y']})

#### Rodillas (Knees)
![LEFT_KNEE_X]({image_paths['LEFT_KNEE_X']})
![LEFT_KNEE_Y]({image_paths['LEFT_KNEE_Y']})
![RIGHT_KNEE_X]({image_paths['RIGHT_KNEE_X']})
![RIGHT_KNEE_Y]({image_paths['RIGHT_KNEE_Y']})

#### Tobillos (Ankles)
![LEFT_ANKLE_X]({image_paths['LEFT_ANKLE_X']})
![LEFT_ANKLE_Y]({image_paths['LEFT_ANKLE_Y']})
![RIGHT_ANKLE_X]({image_paths['RIGHT_ANKLE_X']})
![RIGHT_ANKLE_Y]({image_paths['RIGHT_ANKLE_Y']})

"""
        report_path = os.path.join(self.report_dir, "report.md")
        with open(report_path, "w") as f:
            f.write(md_content)

        print(f"¡Reporte completo! -> {report_path}") 