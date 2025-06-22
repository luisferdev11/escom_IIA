"""
Script para realizar regresión simbólica en el dataset Strogatz Predator-Prey.

Este script carga los datos, los divide en conjuntos de entrenamiento y prueba,
y utiliza la biblioteca 'feyn' para encontrar modelos matemáticos que describan
la dinámica del sistema.

Para ejecutar, asegúrate de tener las bibliotecas necesarias:
pip install pandas feyn scikit-learn matplotlib
"""

import pandas as pd
import feyn


def load_data(filepath):
    """
    Carga el conjunto de datos desde un archivo TSV.

    Args:
        filepath (str): La ruta al archivo .tsv.

    Returns:
        pandas.DataFrame: El DataFrame con los datos cargados o None si hay un error.
    """
    try:
        df = pd.read_csv(filepath, sep='	')
        print(f"Datos cargados exitosamente desde '{filepath}'.")
        return df
    except FileNotFoundError:
        print(f"Error: El archivo '{filepath}' no fue encontrado.")
        return None


def run_symbolic_regression(train_data, target_name, random_seed=42):
    """
    Ejecuta el algoritmo de regresión simbólica de feyn.

    Args:
        train_data (pandas.DataFrame): DataFrame de entrenamiento.
        target_name (str): Nombre de la columna objetivo.
        random_seed (int): Semilla para la aleatoriedad para reproducibilidad.

    Returns:
        list: Una lista de los modelos encontrados por feyn.
    """
    print("\nInicializando QLattice y ejecutando auto_run...")
    ql = feyn.QLattice(random_seed=random_seed)
    models = ql.auto_run(
        data=train_data,
        output_name=target_name
    )
    print("Búsqueda de modelos completada.")
    return models


def main():
    """
    Función principal para orquestar el proceso de regresión simbólica.
    """
    # --- Configuración ---
    DATA_FILE = 'strogatz_predprey1.tsv'
    TARGET_VARIABLE = 'target'
    TRAIN_TEST_RATIO = [0.8, 0.2]
    RANDOM_STATE = 42

    # --- Carga de datos ---
    df = load_data(DATA_FILE)
    if df is None:
        return

    print("\nPrimeras 5 filas del dataset:")
    print(df.head())

    # --- División de datos ---
    print(f"\nDividiendo los datos en {TRAIN_TEST_RATIO[0]*100}% entrenamiento y {TRAIN_TEST_RATIO[1]*100}% prueba...")
    train, test = feyn.tools.split(df, ratio=TRAIN_TEST_RATIO, random_state=RANDOM_STATE)
    print(f"Tamaño del conjunto de entrenamiento: {len(train)} filas")
    print(f"Tamaño del conjunto de prueba: {len(test)} filas")

    # --- Regresión Simbólica ---
    models = run_symbolic_regression(train, TARGET_VARIABLE, random_seed=RANDOM_STATE)

    # --- Muestra de resultados ---
    if not models:
        print("\nNo se encontraron modelos.")
        return

    print("\n--- Mejores Modelos Encontrados ---")
    for i, model in enumerate(models[:3]):
        print(f"\nModelo #{i+1}:")
        print(f"  Ecuación: {model.sympify()}")
        
        # Calcular y mostrar métricas de rendimiento
        try:
            summary = feyn.metrics.get_summary_information(model, test)
            print("  Métricas (en conjunto de prueba):")
            for metric, value in summary.items():
                print(f"    {metric}: {value:.4f}")
        except Exception as e:
            print(f"  No se pudieron calcular las métricas: {e}")

    # --- Visualización del mejor modelo ---
    best_model = models[0]
    plot_filename = "best_model_performance.png"
    print(f"\nGenerando gráfica de rendimiento del mejor modelo. Se guardará como '{plot_filename}'...")

    try:
        best_model.plot(
            data=train,
            compare_data=test,
            filename=plot_filename
        )
        print(f"Gráfica guardada exitosamente.")
    except Exception as e:
        print(f"\nNo se pudo generar la gráfica: {e}")
        print("Aun así, el modelo se ha entrenado y las ecuaciones se han mostrado arriba.")


if __name__ == "__main__":
    main() 