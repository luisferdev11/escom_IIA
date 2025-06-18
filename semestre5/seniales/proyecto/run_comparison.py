import cv2
import numpy as np
import argparse
import os
import mediapipe as mp

from core.pose_logic import process_frame, normalize_pose, calculate_pose_similarity
from core.visualizer import SignalPlotter

# Definir el landmark que queremos rastrear para la señal
# mp_pose.PoseLandmark.RIGHT_WRIST.value -> 16
TRACKED_LANDMARK_INDEX = 16 
# El vector normalizado tiene 3 valores (x,y,z) por landmark. La Y es el segundo valor.
TRACKED_COORDINATE_INDEX = (TRACKED_LANDMARK_INDEX * 3) + 1 

def run_realtime_comparison(video_path, pose_data_path):
    # --- 1. Carga y Validación ---
    if not os.path.exists(pose_data_path):
        print(f"Error: No se encontró el archivo de datos de pose '{pose_data_path}'.")
        print(f"Por favor, ejecuta primero 'preprocess_video.py {video_path} {pose_data_path}' para crearlo.")
        return

    # Cargar el array de diccionarios
    reference_data = np.load(pose_data_path, allow_pickle=True)
    # Extraer los datos necesarios en listas separadas
    reference_poses_normalized = [d["normalized_vector"] for d in reference_data]
    reference_landmarks_list = [d["landmarks"] for d in reference_data]
    
    cap_ref = cv2.VideoCapture(video_path)
    cap_user = cv2.VideoCapture(0)

    if not cap_ref.isOpened() or not cap_user.isOpened():
        print("Error: No se pudo abrir el video de referencia o la cámara del usuario.")
        return

    # --- 2. Inicialización del Visualizador de Señales ---
    # Determinar las dimensiones de los cuadrantes basado en la cámara del usuario
    user_w = int(cap_user.get(cv2.CAP_PROP_FRAME_WIDTH))
    user_h = int(cap_user.get(cv2.CAP_PROP_FRAME_HEIGHT))
    q_w, q_h = user_w // 2, user_h // 2
    quadrant_dims = (q_w, q_h)

    # Extraer la señal de la coordenada Y de la muñeca derecha de los datos de referencia
    ref_signal = [
        pose[TRACKED_COORDINATE_INDEX] if pose is not None else np.nan 
        for pose in reference_poses_normalized
    ]
    # Inicializar el plotter con las dimensiones del cuadrante
    plotter = SignalPlotter(ref_signal, width=q_w, height=q_h)
    
    # --- 3. Bucle Principal ---
    frame_idx = 0
    mp_drawing = mp.solutions.drawing_utils
    mp_pose = mp.solutions.pose

    while cap_user.isOpened() and frame_idx < len(reference_poses_normalized):
        ret_user, user_frame = cap_user.read()
        ret_ref, ref_frame = cap_ref.read()

        if not ret_user or not ret_ref:
            print("Finalizando: video de referencia o captura de cámara terminada.")
            break

        # --- Procesamiento y Lógica ---
        user_landmarks = process_frame(user_frame)
        user_pose_vec = normalize_pose(user_landmarks)
        
        ref_pose_vec = reference_poses_normalized[frame_idx]
        
        score = calculate_pose_similarity(user_pose_vec, ref_pose_vec)

        # --- Actualización del Gráfico de Señal ---
        user_signal_value = user_pose_vec[TRACKED_COORDINATE_INDEX] if user_pose_vec is not None else np.nan
        plot_image = plotter.update(user_signal_value)

        # --- Visualización ---
        # A. Dibuja sobre el frame del usuario (tamaño completo)
        mp_drawing.draw_landmarks(user_frame, user_landmarks, mp_pose.POSE_CONNECTIONS,
                                  mp_drawing.DrawingSpec(color=(245, 117, 66), thickness=2, circle_radius=2),
                                  mp_drawing.DrawingSpec(color=(245, 66, 230), thickness=2, circle_radius=2))
        cv2.putText(user_frame, f'Puntaje: {int(score)}%', (10, 40), cv2.FONT_HERSHEY_TRIPLEX, 1, (0, 255, 0), 2)

        # B. Crea la vista del esqueleto de referencia
        skeleton_view = np.zeros((q_h, q_w, 3), dtype=np.uint8)
        ref_landmarks = reference_landmarks_list[frame_idx]
        if ref_landmarks:
            mp_drawing.draw_landmarks(skeleton_view, ref_landmarks, mp_pose.POSE_CONNECTIONS,
                                      mp_drawing.DrawingSpec(color=(0, 255, 255), thickness=2, circle_radius=1),
                                      mp_drawing.DrawingSpec(color=(255, 255, 0), thickness=2, circle_radius=1))

        # C. Redimensiona los frames de video a tamaño de cuadrante
        ref_frame_resized = cv2.resize(ref_frame, quadrant_dims)
        user_frame_resized = cv2.resize(user_frame, quadrant_dims)

        # D. Ensambla la parrilla 2x2
        top_row = np.hstack([ref_frame_resized, user_frame_resized])
        bottom_row = np.hstack([plot_image, skeleton_view])
        combined_view = np.vstack([top_row, bottom_row])

        cv2.imshow('RitMEAB - Analisis 2x2', combined_view)

        frame_idx += 1
        if cv2.waitKey(10) & 0xFF == ord('q'):
            break

    cap_user.release()
    cap_ref.release()
    cv2.destroyAllWindows()
    for i in range(5): cv2.waitKey(1)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Compara la pose de la cámara en tiempo real con datos de pose pre-procesados.")
    parser.add_argument("video_ref", type=str, help="Ruta al video de referencia original (ej. 'baile.mp4').")
    parser.add_argument("pose_data", type=str, help="Ruta a los datos de pose pre-procesados (ej. 'baile_data.npy').")

    args = parser.parse_args()

    run_realtime_comparison(args.video_ref, args.pose_data) 