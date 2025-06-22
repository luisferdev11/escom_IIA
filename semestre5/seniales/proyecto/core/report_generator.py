import matplotlib.pyplot as plt
import numpy as np
import mediapipe as mp

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