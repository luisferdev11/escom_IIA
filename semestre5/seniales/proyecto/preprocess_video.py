import cv2
import numpy as np
import argparse
from tqdm import tqdm
import os

from core.pose_logic import process_frame, normalize_pose

def extract_and_save_poses(video_path, output_path):
    """
    Extrae, normaliza y guarda las poses de un video en un archivo .npy.
    Ahora guarda tanto los landmarks originales como el vector normalizado.

    Args:
        video_path (str): Ruta al video de entrada.
        output_path (str): Ruta donde se guardará el archivo .npy de poses.
    """
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        print(f"Error: No se pudo abrir el video en '{video_path}'")
        return

    frame_count = int(cap.get(cv2.CAP_PROP_FRAME_COUNT))
    all_pose_data = []

    print(f"Procesando video: {os.path.basename(video_path)}")
    # Usamos tqdm para tener una barra de progreso
    for _ in tqdm(range(frame_count), desc="Extrayendo poses"):
        ret, frame = cap.read()
        if not ret:
            break
        
        # Extraer landmarks y normalizarlos
        landmarks = process_frame(frame)
        normalized_pose_vec = normalize_pose(landmarks)
        
        # Guardar ambos en un diccionario para este fotograma
        pose_data = {
            "landmarks": landmarks,
            "normalized_vector": normalized_pose_vec
        }
        all_pose_data.append(pose_data)

    cap.release()

    # Guardar la lista de diccionarios como un array de NumPy
    np.save(output_path, np.array(all_pose_data, dtype=object))
    print(f"¡Procesamiento completo! Poses guardadas en '{output_path}'")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Procesa un video de referencia para extraer y guardar los datos de pose.")
    parser.add_argument("video_input", type=str, help="Ruta al archivo de video de entrada (ej. 'baile.mp4').")
    parser.add_argument("data_output", type=str, help="Ruta para guardar los datos de pose procesados (ej. 'baile_data.npy').")

    args = parser.parse_args()

    # Validar que el video de entrada exista
    if not os.path.exists(args.video_input):
        print(f"Error: El archivo de video '{args.video_input}' no fue encontrado.")
    else:
        extract_and_save_poses(args.video_input, args.data_output) 