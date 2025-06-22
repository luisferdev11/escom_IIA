import numpy as np

def apply_ema(signal, alpha=0.1):
    """
    Aplica un filtro de Media Móvil Exponencial (EMA) a una señal.

    Args:
        signal (list or np.array): La señal de entrada. Puede contener NaNs.
        alpha (float): El factor de suavizado (smoothing factor). 
                       Un valor más bajo resulta en más suavizado.

    Returns:
        np.array: La señal suavizada.
    """
    signal = np.array(signal, dtype=float)
    smoothed = np.full_like(signal, np.nan)
    
    # Encontrar el primer valor válido para empezar
    first_valid_idx = np.where(np.isfinite(signal))[0]
    if len(first_valid_idx) == 0:
        return smoothed # Devolver NaNs si no hay datos válidos

    # El primer punto de la señal suavizada es el primer punto válido de la original
    start_idx = first_valid_idx[0]
    smoothed[start_idx] = signal[start_idx]

    # Aplicar EMA al resto de la señal
    for i in range(start_idx + 1, len(signal)):
        if np.isnan(signal[i]):
            # Si el valor actual es NaN, mantenemos el último valor suavizado
            smoothed[i] = smoothed[i-1]
        else:
            # Si el valor anterior suavizado era NaN (caso de huecos), reiniciamos
            if np.isnan(smoothed[i-1]):
                 smoothed[i] = signal[i]
            else:
                 smoothed[i] = alpha * signal[i] + (1 - alpha) * smoothed[i-1]
                 
    return smoothed 