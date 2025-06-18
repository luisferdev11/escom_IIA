import random
from functools import cmp_to_key

def repair(chromosome, weights, values, capacity):
    """
    Repara el cromosoma para que cumpla con la restricción de la mochila.
    Se eliminan los elementos con menor relación valor/peso mientras se exceda la capacidad.
    """
    total_weight = sum(weights[i] * chromosome[i] for i in range(len(chromosome)))
    if total_weight <= capacity:
        return chromosome

    # Obtiene índices de los artículos incluidos y los ordena por eficiencia creciente.
    included_items = [i for i, gene in enumerate(chromosome) if gene == 1]
    included_items.sort(key=lambda i: values[i] / weights[i])
    for i in included_items:
        if total_weight <= capacity:
            break
        chromosome[i] = 0
        total_weight -= weights[i]
    return chromosome

def generate_random_chromosome(length, weights, values, capacity):
    """
    Genera un cromosoma aleatorio (lista de 0s y 1s) y lo repara para que sea factible.
    """
    chromosome = [random.randint(0, 1) for _ in range(length)]
    return repair(chromosome, weights, values, capacity)

def fitness(chromosome, values, weights, capacity):
    """
    Calcula el fitness del cromosoma.
    Si el cromosoma es viable (peso total <= capacidad) retorna la suma total del valor,
    de lo contrario se descarta (retorna -infinito).
    """
    total_weight = sum(weights[i] * chromosome[i] for i in range(len(chromosome)))
    if total_weight > capacity:
        return -float('inf')
    return sum(values[i] * chromosome[i] for i in range(len(chromosome)))

def compare_chromosomes(a, b, values, weights, capacity):
    """
    Función de comparación para ordenar cromosomas:
    - Mayor fitness es mejor.
    - Empate: menor peso total es preferible.
    """
    fa = fitness(a, values, weights, capacity)
    fb = fitness(b, values, weights, capacity)
    if fa != fb:
        return fb - fa  # Orden descendente por fitness.
    weight_a = sum(weights[i] * a[i] for i in range(len(a)))
    weight_b = sum(weights[i] * b[i] for i in range(len(b)))
    return weight_a - weight_b

def next_generation(population, values, weights, capacity, mutation_prob):
    """
    Genera la siguiente generación mediante elitismo y selección por torneo.
    Se mantiene a los dos mejores cromosomas y se crea descendencia mediante cruce y mutación.
    """
    population.sort(key=cmp_to_key(lambda a, b: compare_chromosomes(a, b, values, weights, capacity)))
    new_population = population[:2]  # Elitismo: conservar los dos mejores.

    while len(new_population) < len(population):
        # Selección por torneo (se eligen 4 candidatos y se toman los 2 mejores)
        candidates = random.sample(population, 4)
        candidates.sort(key=cmp_to_key(lambda a, b: compare_chromosomes(a, b, values, weights, capacity)))
        parent1, parent2 = candidates[:2]
        
        # Cruce de un punto (punto de corte aleatorio)
        length = len(parent1)
        split = random.randint(1, length - 1)
        child1 = parent1[:split] + parent2[split:]
        child2 = parent2[:split] + parent1[split:]
        
        # Mutación: invertir el bit en una posición aleatoria con probabilidad mutation_prob.
        for child in [child1, child2]:
            if random.random() < mutation_prob:
                idx = random.randint(0, length - 1)
                child[idx] ^= 1  # Cambio de 0 a 1 o viceversa.
            new_population.append(repair(child, weights, values, capacity))
            if len(new_population) >= len(population):
                break

    return new_population[:len(population)]

def run_knapsack_ga(generations=50, num_items=20, population_size=10, mutation_prob=0.25, capacity=1.0):
    """
    Ejecuta el algoritmo genético para el problema de la mochila.
    Se generan valores y pesos aleatorios para cada artículo.
    """
    # Generación de datos: pesos y valores de cada artículo.
    values = [random.randint(1, 100) for _ in range(num_items)]
    weights = [random.uniform(0.01, 0.99) for _ in range(num_items)]
    print("Pesos:", weights)
    print("Valores:", values)
    
    # Inicialización de la población.
    population = [generate_random_chromosome(num_items, weights, values, capacity)
                  for _ in range(population_size)]
    
    # Ciclo evolutivo.
    for gen in range(generations):
        population.sort(key=cmp_to_key(lambda a, b: compare_chromosomes(a, b, values, weights, capacity)))
        best = population[0]
        best_val = fitness(best, values, weights, capacity)
        best_weight = sum(weights[i] * best[i] for i in range(num_items))
        print(f"\nGeneración {gen+1}")
        for ind in population:
            ind_weight = sum(weights[i] * ind[i] for i in range(num_items))
            print(f"  Cromosoma: {ind}, Valor: {fitness(ind, values, weights, capacity)}, Peso: {ind_weight:.2f}")
        print(f"Mejor solución - Valor: {best_val}, Peso: {best_weight:.2f}")
        
        population = next_generation(population, values, weights, capacity, mutation_prob)
        
    population.sort(key=cmp_to_key(lambda a, b: compare_chromosomes(a, b, values, weights, capacity)))
    best = population[0]
    print("\n=== Solución Óptima ===")
    print(f"Valor total: {fitness(best, values, weights, capacity)}")
    print(f"Peso total: {sum(weights[i] * best[i] for i in range(num_items)):.2f}")
    print(f"Artículos seleccionados: {best}")

if __name__ == "__main__":
    run_knapsack_ga()
