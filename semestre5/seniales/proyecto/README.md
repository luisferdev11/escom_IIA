# RitMEAB - Prototipo de Análisis de Baile

Este proyecto es un prototipo para un sistema de análisis de baile que utiliza visión por computadora para comparar los movimientos de un usuario en tiempo real con una coreografía de referencia, mostrando una parrilla de análisis 2x2.

---

## Características

- **Análisis Modular:** El código está separado en módulos para pre-procesamiento y análisis en tiempo real.
- **Visualización 2x2:** Muestra simultáneamente el video de referencia, la cámara del usuario, un esqueleto de referencia aislado y una gráfica de señales.
- **Pre-procesamiento Eficiente:** Un script dedicado analiza el video de referencia una sola vez, generando un archivo de datos para un inicio casi instantáneo de la aplicación principal.
- **Análisis de Señales:** Grafica la trayectoria de un punto corporal (ej. muñeca) a lo largo del tiempo para un análisis detallado del movimiento.

---

## Estructura del Proyecto

El proyecto está organizado en una estructura limpia para facilitar la mantenibilidad y escalabilidad.

```
.
├── core/
│   ├── pose_logic.py     # Lógica central para detección y análisis de poses.
│   └── visualizer.py     # Clase para generar el gráfico de señales.
├── preprocess_video.py     # Script para procesar el video de referencia.
├── run_comparison.py       # Script principal para ejecutar la aplicación.
├── requirements.txt        # Lista de dependencias de Python.
├── README.md               # Este archivo.
└── .venv/                    # Directorio del entorno virtual (ignorado por Git).
```

### Descripción de Componentes

- **`core/`**: Este directorio es el corazón del proyecto y contiene toda la lógica de negocio reutilizable.

  - `pose_logic.py`: Encapsula toda la interacción con MediaPipe. Se encarga de procesar fotogramas, normalizar coordenadas y calcular la similitud entre poses.
  - `visualizer.py`: Contiene la clase `SignalPlotter`, responsable de crear y actualizar el gráfico de Matplotlib y convertirlo en una imagen que OpenCV pueda mostrar.

- **`preprocess_video.py`**: Una herramienta de línea de comandos que se ejecuta una vez por cada video. Analiza la coreografía, extrae los datos de pose (landmarks y vectores normalizados) y los guarda en un archivo `.npy` comprimido para su uso posterior.

- **`run_comparison.py`**: El punto de entrada para el usuario final. Carga los datos pre-procesados, inicia la cámara y organiza la parrilla de visualización 2x2, orquestando los módulos del directorio `core`.

---

## Cómo Usarlo

Sigue estos pasos para ejecutar el prototipo.

### 1. Configuración del Entorno

Asegúrate de tener Python 3.8+ instalado. Luego, crea un entorno virtual e instala las dependencias.

```bash
# Crear y activar un entorno virtual (en Linux/macOS)
python3 -m venv .venv
source .venv/bin/activate

# Instalar las dependencias
pip install -r requirements.txt
```

### 2. Consigue un Video de Referencia

Busca un video de un baile que quieras imitar. Guárdalo en el directorio raíz del proyecto. Para este ejemplo, supongamos que se llama `baile.mp4`.

### 3. Pre-procesa el Video

Ahora, usa el script `preprocess_video.py` para analizar el video y crear el archivo de datos de la coreografía. Este paso solo se hace una vez por video.

- El primer argumento es el video de entrada.
- El segundo argumento es el archivo de salida donde se guardarán los datos.

```bash
python3 preprocess_video.py baile.mp4 baile_data.npy
```

Verás una barra de progreso mientras se procesa el video. Al terminar, tendrás un nuevo archivo `baile_data.npy` en tu directorio.

### 4. Ejecuta la Comparación en Tiempo Real

¡Es hora de bailar! Ejecuta el script `run_comparison.py`.

- El primer argumento es el video de referencia original (para visualización).
- El segundo argumento es el archivo de datos de pose que acabas de crear.

```bash
python3 run_comparison.py baile.mp4 baile_data.npy
```

Se abrirá una ventana mostrando la parrilla de análisis 2x2. Presiona la tecla `q` para salir.
