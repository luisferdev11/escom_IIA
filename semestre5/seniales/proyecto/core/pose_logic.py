import mediapipe as mp
import numpy as np
import cv2

# Inicializar el modelo de pose de MediaPipe una sola vez
mp_pose = mp.solutions.pose
pose_estimator = mp_pose.Pose(min_detection_confidence=0.5, min_tracking_confidence=0.5)

def process_frame(frame):
    """
    Procesa un solo fotograma para detectar y devolver los landmarks de la pose.
    
    Args:
        frame: Un fotograma de video (array de NumPy en formato BGR).
        
    Returns:
        Los landmarks de pose detectados por MediaPipe.
    """
    # Convertir a RGB para MediaPipe
    image = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    image.flags.writeable = False
    
    # Procesar para obtener la pose
    results = pose_estimator.process(image)
    
    return results.pose_landmarks

def normalize_pose(landmarks):
    """
    Normaliza los landmarks de una pose para que sean invariantes a la escala y la traslación.
    Se centra en las caderas y se escala por el tamaño del torso.
    
    Args:
        landmarks: Los landmarks de una pose de MediaPipe.
        
    Returns:
        Un array de NumPy 1D con las coordenadas normalizadas, o None si no hay landmarks.
    """
    if not landmarks:
        return None
    
    coords = np.array([[lm.x, lm.y, lm.z] for lm in landmarks.landmark])

    # 1. Calcular el centro de las caderas como origen
    hip_center = (coords[mp_pose.PoseLandmark.LEFT_HIP.value] + coords[mp_pose.PoseLandmark.RIGHT_HIP.value]) * 0.5
    coords -= hip_center
    
    # 2. Calcular la escala basada en el tamaño del torso
    left_shoulder = coords[mp_pose.PoseLandmark.LEFT_SHOULDER.value]
    right_shoulder = coords[mp_pose.PoseLandmark.RIGHT_SHOULDER.value]
    shoulder_center = (left_shoulder + right_shoulder) * 0.5
    torso_size = np.linalg.norm(shoulder_center - hip_center)
    
    # 3. Normalizar por tamaño del torso
    if torso_size > 1e-5:
        coords /= torso_size
    
    return coords.flatten()

def calculate_pose_similarity(vec1, vec2):
    """
    Calcula la similitud de coseno entre dos vectores de pose normalizados.
    
    Args:
        vec1: El primer vector de pose normalizado.
        vec2: El segundo vector de pose normalizado.
        
    Returns:
        Un puntaje de similitud de 0 a 100.
    """
    if vec1 is None or vec2 is None:
        return 0
        
    # Similitud de Coseno
    dot_product = np.dot(vec1, vec2)
    norm_vec1 = np.linalg.norm(vec1)
    norm_vec2 = np.linalg.norm(vec2)
    
    if norm_vec1 == 0 or norm_vec2 == 0:
        return 0
        
    similarity = dot_product / (norm_vec1 * norm_vec2)
    
    # Mapear de [-1, 1] a [0, 100]
    score = (similarity + 1) / 2 * 100
    # escala la similitud de pose pues tiende a ser muy alta
    score = scale_pose_similarity(score)
    return score 

def scale_pose_similarity(score):
    """
    Escala la similitud de pose para hacerla más interpretable.
    Los valores muy altos (95+) se reducen para mostrar diferencias más claras.
    
    Args:
        score: Puntaje de similitud original (0-100)
        
    Returns:
        Puntaje escalado (0-100)
    """
    # Aplicar una función de escalado no lineal
    # Valores bajos se mantienen similares, valores altos se reducen más
    if score < 80:
        return score
    elif score < 90:
        # Entre 80-90, reducir ligeramente
        return 80 + (score - 80) * 0.7
    elif score < 95:
        # Entre 90-95, reducir más
        return 87 + (score - 90) * 0.6
    else:
        # 95+ se mapea a 87-95
        return 87 + (score - 95) * 1.6

