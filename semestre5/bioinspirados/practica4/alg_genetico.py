import tkinter as tk
from tkinter import ttk
import random
import math
import numpy as np
import matplotlib
# Usamos TkAgg para la integración con Tkinter
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# =============================
# Parámetros del problema y del AG
# =============================

# Rango de búsqueda para cada dimensión
X_MIN, X_MAX = -5.12, 5.12
Y_MIN, Y_MAX = -5.12, 5.12

# Bits para cada dimensión y total del cromosoma (x e y)
BITS_DIM = 16
L_CHROMOSOME = BITS_DIM * 2

# Parámetros AG
POP_SIZE = 25          # Tamaño de la población
TORNEO_SIZE = 3        # Tamaño del torneo en la selección
P_CROSS = 0.8          # Probabilidad de cruce
P_MUT = 0.2           # Probabilidad de mutación por bit
ELITE = 2              # Cantidad de individuos elite que se conservan
MAX_GENERATIONS = 25   # Máximo número de generaciones

# =============================
# Funciones del Algoritmo Genético
# =============================

def rastrigin(x, y):
    """
    Función Rastrigin en 2D:
    f(x,y) = 20 + (x^2 - 10*cos(2*pi*x)) + (y^2 - 10*cos(2*pi*y))
    Se usa np.cos y np.pi para trabajar con arrays de NumPy o escalares.
    """
    A = 10
    return 2 * A + (x**2 - A * np.cos(2 * np.pi * x)) + (y**2 - A * np.cos(2 * np.pi * y))

def decode_chromosome(chrom):
    """
    Decodifica un cromosoma (lista de 0s y 1s) en dos valores reales (x,y)
    """
    x_bits = chrom[:BITS_DIM]
    y_bits = chrom[BITS_DIM:]
    x_int = int("".join(str(bit) for bit in x_bits), 2)
    y_int = int("".join(str(bit) for bit in y_bits), 2)
    max_int = 2**BITS_DIM - 1
    x_val = X_MIN + (X_MAX - X_MIN) * x_int / max_int
    y_val = Y_MIN + (Y_MAX - Y_MIN) * y_int / max_int
    return x_val, y_val

def random_chromosome():
    """Genera un cromosoma aleatorio."""
    return [random.randint(0, 1) for _ in range(L_CHROMOSOME)]

def init_population():
    """Inicializa la población aleatoriamente."""
    return [random_chromosome() for _ in range(POP_SIZE)]

def evaluate_population(pop):
    """
    Evalúa la población: se calcula la función Rastrigin para cada cromosoma.
    Se define la aptitud como fitness = 1/(1 + f(x,y)) para favorecer mínimos.
    """
    fitnesses = []
    for chrom in pop:
        x, y = decode_chromosome(chrom)
        f_val = rastrigin(x, y)
        fitnesses.append(1.0 / (1.0 + f_val))
    return fitnesses

def torneo_selection(pop, fitnesses):
    """Realiza selección por torneo."""
    selected = []
    pop_fit = list(zip(pop, fitnesses))
    for _ in range(POP_SIZE):
        contenders = random.sample(pop_fit, TORNEO_SIZE)
        winner = max(contenders, key=lambda item: item[1])[0]
        selected.append(winner)
    return selected

def crossover(parent1, parent2):
    """Cruce de un punto."""
    if random.random() < P_CROSS:
        point = random.randint(1, L_CHROMOSOME - 1)
        child1 = parent1[:point] + parent2[point:]
        child2 = parent2[:point] + parent1[point:]
        return child1, child2
    else:
        return parent1[:], parent2[:]

def mutate(chrom):
    """Mutación bit a bit."""
    for i in range(len(chrom)):
        if random.random() < P_MUT:
            chrom[i] = 1 - chrom[i]
    return chrom

# =============================
# Función para imprimir información en consola
# =============================
def print_generation_info(generation, pop):
    """
    Imprime en consola la información de cada cromosoma de la población.
    Se muestra: número de cromosoma, representación binaria, (x,y) y f(x,y)
    """
    print(f"Soluciones de la generación {generation}:")
    for i, chrom in enumerate(pop, 1):
        bin_str = "".join(str(bit) for bit in chrom)
        x, y = decode_chromosome(chrom)
        f_val = rastrigin(x, y)
        print(f"  {i}: {bin_str} -> ({x:.4f}, {y:.4f}) -> f({x:.4f}, {y:.4f}) = {f_val:.4f}")
    print("-" * 70)

# =============================
# Variables Globales del AG
# =============================
population = init_population()
best_chromosome = population[0]
best_value = float('inf')
generation_count = 0
best_values_over_time = []

# Imprimir la generación inicial (generación 0)
print_generation_info(generation_count, population)

# =============================
# Funciones para la GUI
# =============================

def plot_population(ax):
    """
    Dibuja la función Rastrigin y la posición de los individuos en la población.
    """
    ax.clear()
    # Crear malla para graficar la función
    resolution = 100
    x_vals = np.linspace(X_MIN, X_MAX, resolution)
    y_vals = np.linspace(Y_MIN, Y_MAX, resolution)
    X, Y = np.meshgrid(x_vals, y_vals)
    Z = rastrigin(X, Y)
    
    # Contornos de la función
    ax.contourf(X, Y, Z, levels=50, cmap='viridis')
    
    # Extraer posiciones de la población
    xs, ys = [], []
    for chrom in population:
        x, y = decode_chromosome(chrom)
        xs.append(x)
        ys.append(y)
    ax.scatter(xs, ys, c='red', label='Población')
    
    # Marcar la mejor solución actual
    if best_chromosome is not None:
        bx, by = decode_chromosome(best_chromosome)
        ax.scatter([bx], [by], c='white', edgecolors='black', s=100, label='Mejor')
    
    ax.set_title(f"Generación {generation_count} - Mejor: {best_value:.4f}")
    ax.set_xlim(X_MIN, X_MAX)
    ax.set_ylim(Y_MIN, Y_MAX)
    ax.legend()

def next_generation():
    """
    Ejecuta una generación del algoritmo genético, actualiza la población, la gráfica y
    muestra en consola la información de la nueva generación.
    """
    global population, best_chromosome, best_value, generation_count, best_values_over_time

    generation_count += 1
    fitnesses = evaluate_population(population)
    
    # Actualizar la mejor solución
    for chrom in population:
        x, y = decode_chromosome(chrom)
        val = rastrigin(x, y)
        if val < best_value:
            best_value = val
            best_chromosome = chrom[:]
    best_values_over_time.append(best_value)
    
    # Selección y cruce con elitismo
    sorted_pop = [p for p, _ in sorted(zip(population, fitnesses),
                                        key=lambda x: x[1], reverse=True)]
    next_pop = sorted_pop[:ELITE]  # elitismo
    
    selected = torneo_selection(population, fitnesses)
    while len(next_pop) < POP_SIZE:
        p1 = random.choice(selected)
        p2 = random.choice(selected)
        child1, child2 = crossover(p1, p2)
        next_pop.append(mutate(child1))
        if len(next_pop) < POP_SIZE:
            next_pop.append(mutate(child2))
    population = next_pop

    # Imprimir en consola la información de la generación actual
    print_generation_info(generation_count, population)

    # Actualizar la gráfica en el canvas
    plot_population(ax)
    canvas.draw()
    
    # Si se llega al máximo de generaciones, se deshabilita el botón.
    if generation_count >= MAX_GENERATIONS:
        btn_next.config(state=tk.DISABLED)
        print("Se alcanzó el número máximo de generaciones.")
        print(f"Mejor solución: {decode_chromosome(best_chromosome)} con f(x,y) = {best_value:.4f}")

# =============================
# Configuración de la Interfaz Tkinter
# =============================
root = tk.Tk()
root.title("Algoritmo Genético - Minimización de Rastrigin")

# Creamos la figura de matplotlib
fig, ax = plt.subplots(figsize=(6, 5))
plot_population(ax)

# Integrar la figura en Tkinter
canvas = FigureCanvasTkAgg(fig, master=root)
canvas_widget = canvas.get_tk_widget()
canvas_widget.pack(side=tk.TOP, fill=tk.BOTH, expand=1)

# Botón para la siguiente generación
btn_next = ttk.Button(root, text="Next Generation", command=next_generation)
btn_next.pack(side=tk.BOTTOM, pady=10)

# Ejecutar la interfaz
root.mainloop()
