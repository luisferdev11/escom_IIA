# RitMEAB - Prototipo de Análisis de Baile

Este proyecto es un prototipo para un sistema de análisis de baile que utiliza visión por computadora para comparar los movimientos de un usuario en tiempo real con una coreografía de referencia, mostrando una parrilla de análisis 2x2.

Al finalizar la sesión, genera un reporte detallado en Markdown con métricas de rendimiento y gráficos comparativos que analizan la precisión y la fluidez del movimiento.

---

## Características

- **Análisis Modular:** El código está separado en módulos para pre-procesamiento, lógica de pose, motor de puntuación, análisis de señales y generación de reportes.
- **Visualización 2x2:** Muestra simultáneamente el video de referencia, la cámara del usuario, un esqueleto de referencia aislado y una gráfica de señales en tiempo real.
- **Motor de Puntuación Avanzado:**
  - **Precisión Ponderada:** Da más importancia a las articulaciones clave (caderas, hombros) para una evaluación más realista de la postura.
  - **Análisis de Dinámica:** Compara la velocidad de movimiento entre el usuario y la referencia, premiando no solo la pose correcta, sino el movimiento correcto.
- **Reportes Post-Sesión Detallados:**
  - Genera automáticamente una carpeta por cada sesión con un reporte en formato Markdown.
  - Incluye métricas clave como Puntuación Media, Consistencia y la identificación de las articulaciones con mejor y peor rendimiento.
  - **Análisis con Filtro EMA:** Muestra gráficos comparativos de articulaciones y precisión, contrastando los datos en crudo (Raw) con una versión suavizada (EMA) para visualizar la tendencia real del movimiento.

---

## Estructura del Proyecto

El proyecto está organizado en una estructura limpia para facilitar la mantenibilidad y escalabilidad.

```
.
├── core/
│   ├── pose_logic.py          # Lógica central para detección y análisis de poses.
│   ├── scoring_engine.py      # Clase para el cálculo de puntuación (precisión + dinámica).
│   ├── signal_processing.py   # Funciones de utilidad para análisis de señales (ej. filtro EMA).
│   └── visualizer.py          # Clase para generar el gráfico de señales en tiempo real.
├── reports/
│   └── 2023-10-27_10-30-00/   # Ejemplo de carpeta de reporte generada automáticamente.
│       ├── report.md
│       └── ... (imágenes de gráficos)
├── preprocess_video.py        # Script para procesar el video de referencia.
├── run_comparison.py          # Script principal para ejecutar la aplicación.
├── requirements.txt           # Lista de dependencias de Python.
└── README.md                  # Este archivo.
```

### Descripción de Componentes

- **`core/`**: Este directorio es el corazón del proyecto y contiene toda la lógica de negocio reutilizable.

  - `pose_logic.py`: Encapsula la interacción con MediaPipe para procesar fotogramas y normalizar coordenadas.
  - `scoring_engine.py`: Implementa la lógica de evaluación avanzada, combinando precisión ponderada y dinámica de movimiento para generar una puntuación.
  - `signal_processing.py`: Contiene funciones para manipular y analizar las señales de datos, como el filtro de Media Móvil Exponencial (EMA).
  - `visualizer.py`: Gestiona el gráfico de Matplotlib que se muestra en tiempo real durante la sesión.

- **`reports/`**: Este directorio es creado automáticamente y contiene los reportes de cada sesión. Cada subcarpeta, nombrada con fecha y hora, almacena un `report.md` y todos los gráficos asociados.

- **`preprocess_video.py`**: Herramienta de línea de comandos que se ejecuta una vez por video para analizar la coreografía y guardar los datos de pose en un archivo `.npy`.

- **`run_comparison.py`**: El punto de entrada para el usuario. Orquesta todos los módulos, ejecuta la sesión en tiempo real y, al finalizar, dispara la generación del reporte.

---

## Cómo Usarlo

Sigue estos pasos para ejecutar el prototipo.

### 1. Configuración del Entorno

```bash
# Crear y activar un entorno virtual (en Linux/macOS)
python3 -m venv .venv
source .venv/bin/activate

# Instalar las dependencias
pip install -r requirements.txt
```

### 2. Pre-procesa un Video de Referencia

Este paso solo se hace una vez por video.

```bash
python3 preprocess_video.py tu_video.mp4 tus_datos.npy
```

### 3. Ejecuta la Comparación en Tiempo Real

¡Es hora de bailar!

```bash
python3 run_comparison.py tu_video.mp4 tus_datos.npy
```

Se abrirá la ventana de análisis 2x2. Baila y, cuando termines, presiona la tecla `q` para salir.

### 4. Revisa tu Reporte

Al cerrar la aplicación, se generará automáticamente un reporte. Busca la nueva carpeta creada dentro del directorio `reports/` y abre el archivo `report.md` para ver un análisis detallado de tu rendimiento.
