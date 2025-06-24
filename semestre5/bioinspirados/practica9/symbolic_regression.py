import pandas as pd
import feyn
import random
import numpy as np


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


def display_results(models, train_data, test_data, target_name):
    """
    Muestra los mejores modelos y sus métricas de rendimiento.

    Args:
        models (list): Lista de modelos de feyn.
        train_data (pd.DataFrame): DataFrame de entrenamiento.
        test_data (pd.DataFrame): DataFrame de prueba.
        target_name (str): Nombre de la variable objetivo.
    """
    if not models:
        print("\nNo se encontraron modelos.")
        return

    print("\n--- Mejores Modelos Encontrados ---")
    for i, model in enumerate(models[:3]):
        print(f"\nModelo #{i+1}:")
        print(f"  Ecuación: {model.sympify()}")
        
        # Calcular y mostrar métricas de rendimiento
        try:
            summary = feyn.metrics.get_summary_information(model, test_data)
            print("  Métricas (en conjunto de prueba):")
            for metric, value in summary.items():
                print(f"    {metric}: {value:.4f}")
        except Exception as e:
            print(f"  No se pudieron calcular las métricas: {e}")

    # --- Visualización del mejor modelo ---
    best_model = models[0]
    plot_filename = f"best_model_{target_name}_performance.png"
    print(f"\nGenerando gráfica de rendimiento del mejor modelo. Se guardará como '{plot_filename}'...")

    try:
        best_model.plot(
            data=train_data,
            compare_data=test_data,
            filename=plot_filename
        )
        print(f"Gráfica guardada exitosamente.")
    except Exception as e:
        print(f"\nNo se pudo generar la gráfica: {e}")
        print("Aun así, el modelo se ha entrenado y las ecuaciones se han mostrado arriba.")


def run_artificial_data_experiment(random_seed=42):
    """
    Genera un dataset artificial, ejecuta la regresión simbólica y muestra los resultados.
    """
    print("\n" + "="*80)
    print("INICIANDO EXPERIMENTO CON DATASET ARTIFICIAL DE 3 VARIABLES")
    print("="*80 + "\n")

    # --- Generación de datos artificiales ---
    print("Generando dataset artificial...")
    def F(x1, x2, x3):
        """Función de prueba con 3 variables."""
        return x1**2 + np.sin(x2) + x3
    
    print(f"Función de prueba: {F}")

    table = []
    for _ in range(1000):
        x1 = random.uniform(-10, 10)
        x2 = random.uniform(-np.pi, np.pi)
        x3 = random.uniform(-10, 10)
        table.append([F(x1, x2, x3), x1, x2, x3])

    df_artificial = pd.DataFrame(table, columns=['F', 'x1', 'x2', 'x3'])
    print("Dataset artificial generado con 1000 muestras.")
    print("Primeras 5 filas del dataset artificial:")
    print(df_artificial.head())

    # --- División de datos ---
    print("\nDividiendo los datos en 60% entrenamiento y 40% prueba...")
    train_art, test_art = feyn.tools.split(df_artificial, ratio=[0.6, 0.4], random_state=random_seed)
    print(f"Tamaño del conjunto de entrenamiento: {len(train_art)} filas")
    print(f"Tamaño del conjunto de prueba: {len(test_art)} filas")

    # --- Regresión Simbólica ---
    target_variable_art = 'F'
    models_art = run_symbolic_regression(train_art, target_variable_art, random_seed=random_seed)

    # --- Muestra de resultados ---
    display_results(models_art, train_art, test_art, target_variable_art)


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
    display_results(models, train, test, TARGET_VARIABLE)

    # --- Experimento con datos artificiales ---
    run_artificial_data_experiment(random_seed=RANDOM_STATE)


if __name__ == "__main__":
    main() 