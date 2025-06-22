import numpy as np
import mediapipe as mp

mp_pose = mp.solutions.pose

class ScoringEngine:
    """
    Calcula un score de baile combinado basado en precisión ponderada y dinámica de movimiento.
    """
    def __init__(self, precision_weight=0.6, dynamics_weight=0.4):
        self.precision_weight = precision_weight
        self.dynamics_weight = dynamics_weight

        # Estado para el cálculo de la dinámica (velocidad)
        self.user_pose_prev = None
        self.ref_pose_prev = None

        # 1. Definir los pesos por articulación
        self.landmark_weights = {
            # Core del cuerpo, muy importante
            mp_pose.PoseLandmark.LEFT_HIP: 2.0,
            mp_pose.PoseLandmark.RIGHT_HIP: 2.0,
            mp_pose.PoseLandmark.LEFT_SHOULDER: 2.0,
            mp_pose.PoseLandmark.RIGHT_SHOULDER: 2.0,
            # Articulaciones mayores, importantes
            mp_pose.PoseLandmark.LEFT_KNEE: 1.5,
            mp_pose.PoseLandmark.RIGHT_KNEE: 1.5,
            mp_pose.PoseLandmark.LEFT_ELBOW: 1.5,
            mp_pose.PoseLandmark.RIGHT_ELBOW: 1.5,
            # Extremidades, peso normal
            mp_pose.PoseLandmark.LEFT_WRIST: 1.0,
            mp_pose.PoseLandmark.RIGHT_WRIST: 1.0,
            mp_pose.PoseLandmark.LEFT_ANKLE: 1.0,
            mp_pose.PoseLandmark.RIGHT_ANKLE: 1.0,
        }
        # Crear un vector de pesos para la multiplicación eficiente
        self.weight_vector = self._create_weight_vector()

    def _create_weight_vector(self):
        """Genera un vector de pesos que coincide con la estructura del vector de pose."""
        # 33 landmarks, cada uno con 3 coordenadas (x, y, z)
        num_coords = 33 * 3
        weights = np.ones(num_coords)
        for landmark, weight in self.landmark_weights.items():
            idx = landmark.value
            weights[idx*3 : (idx*3)+3] = weight # Aplicar el mismo peso a x, y, z
        return weights

    def _calculate_weighted_precision(self, user_vec, ref_vec):
        """Calcula la similitud de coseno ponderada."""
        if user_vec is None or ref_vec is None:
            return 0
        
        # Aplicar pesos a cada vector antes de calcular la similitud
        weighted_user_vec = user_vec * self.weight_vector
        weighted_ref_vec = ref_vec * self.weight_vector
        
        dot_product = np.dot(weighted_user_vec, weighted_ref_vec)
        norm_user = np.linalg.norm(weighted_user_vec)
        norm_ref = np.linalg.norm(weighted_ref_vec)

        if norm_user == 0 or norm_ref == 0:
            return 0

        similarity = dot_product / (norm_user * norm_ref)
        return (similarity + 1) / 2 * 100

    def _calculate_dynamics(self, user_curr, user_prev, ref_curr, ref_prev):
        """Calcula la similitud de las velocidades de las articulaciones."""
        if any(v is None for v in [user_curr, user_prev, ref_curr, ref_prev]):
            return 0
        
        # Calcular vectores de velocidad
        user_velocity = user_curr - user_prev
        ref_velocity = ref_curr - ref_prev

        # Comparar los vectores de velocidad usando similitud de coseno
        dot_product = np.dot(user_velocity, ref_velocity)
        norm_user = np.linalg.norm(user_velocity)
        norm_ref = np.linalg.norm(ref_velocity)

        if norm_user == 0 or norm_ref == 0:
            return 0
        
        similarity = dot_product / (norm_user * norm_ref)
        return (similarity + 1) / 2 * 100

    def calculate_frame_score(self, user_curr, ref_curr):
        """
        Calcula la puntuación total para el fotograma actual y actualiza el estado.
        """
        precision_score = self._calculate_weighted_precision(user_curr, ref_curr)
        
        # Para el primer fotograma, la dinámica no se puede calcular.
        # Usamos la precisión como un sustituto razonable.
        if self.user_pose_prev is None or self.ref_pose_prev is None:
            dynamics_score = precision_score
        else:
            dynamics_score = self._calculate_dynamics(user_curr, self.user_pose_prev, ref_curr, self.ref_pose_prev)

        # Actualizar estado para el siguiente fotograma
        self.user_pose_prev = user_curr
        self.ref_pose_prev = ref_curr

        # Combinación ponderada
        combined_score = (self.precision_weight * precision_score) + (self.dynamics_weight * dynamics_score)
        
        return combined_score, precision_score, dynamics_score 