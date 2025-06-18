import random
import numpy as np
from functools import cmp_to_key

class TSP_GA:
    def __init__(self, distance_matrix, num_cities=10, population_size=10,
                 mutation_probability=0.25, num_generations=200):
        self.distance_matrix = distance_matrix
        self.num_cities = num_cities
        self.population_size = population_size
        self.mutation_probability = mutation_probability
        self.num_generations = num_generations
        self.population = [self.random_chromosome() for _ in range(population_size)]
    
    def random_chromosome(self):
        """
        Genera una permutación aleatoria de ciudades.
        """
        chromosome = list(range(1, self.num_cities + 1))
        random.shuffle(chromosome)
        return chromosome
    
    def route_distance(self, chromosome):
        """
        Calcula la distancia total de la ruta, incluyendo el regreso a la ciudad inicial.
        """
        total_distance = 0
        for i in range(len(chromosome) - 1):
            total_distance += self.distance_matrix[chromosome[i]][chromosome[i+1]]
        total_distance += self.distance_matrix[chromosome[-1]][chromosome[0]]
        return total_distance
    
    def fitness(self, chromosome):
        """
        Define el fitness como el inverso de la distancia de la ruta.
        """
        return 1 / self.route_distance(chromosome)
    
    def evaluate_population(self):
        """
        Calcula el fitness de cada cromosoma en la población.
        """
        return [self.fitness(chrom) for chrom in self.population]
    
    def compare_chromosomes(self, chrom1, chrom2):
        """
        Función de comparación para ordenar de mayor a menor fitness.
        """
        f1 = self.fitness(chrom1)
        f2 = self.fitness(chrom2)
        return -1 if f1 > f2 else (1 if f1 < f2 else 0)
    
    def order_crossover(self, parent1, parent2):
        """
        Implementa el operador Order Crossover (OX).
        Se selecciona un segmento de parent1 y se completan los genes faltantes en
        el orden en que aparecen en parent2.
        """
        a, b = sorted(random.sample(range(self.num_cities), 2))
        child = [None] * self.num_cities
        child[a:b] = parent1[a:b]
        ptr = b
        for gene in parent2:
            if gene not in child:
                if ptr >= self.num_cities:
                    ptr = 0
                child[ptr] = gene
                ptr += 1
        return child
    
    def mutate(self, chromosome):
        """
        Operador de mutación: intercambia dos posiciones aleatorias.
        """
        a, b = random.sample(range(self.num_cities), 2)
        chromosome[a], chromosome[b] = chromosome[b], chromosome[a]
        return chromosome
    
    def next_generation(self):
        """
        Genera la siguiente generación empleando elitismo y selección ponderada.
        """
        self.population.sort(key=cmp_to_key(self.compare_chromosomes))
        new_population = self.population[:2]  # Elitismo: conservar los dos mejores.
        
        while len(new_population) < self.population_size:
            fitness_values = self.evaluate_population()
            parent1, parent2 = random.choices(self.population, weights=fitness_values, k=2)
            child1 = self.order_crossover(parent1, parent2)
            child2 = self.order_crossover(parent2, parent1)
            if random.random() < self.mutation_probability:
                child1 = self.mutate(child1)
            if random.random() < self.mutation_probability:
                child2 = self.mutate(child2)
            new_population.append(child1)
            if len(new_population) < self.population_size:
                new_population.append(child2)
        self.population = new_population
    
    def run(self):
        """
        Ejecuta el ciclo evolutivo durante el número de generaciones especificado,
        mostrando en cada iteración la mejor solución.
        """
        print("Algoritmo Genético para el TSP (10 ciudades)")
        print("Matriz de distancias:")
        print(self.distance_matrix)
        print("\nPoblación inicial:")
        for idx, chrom in enumerate(self.population):
            print(f"  Cromo {idx+1:2d}: {chrom}, Distancia: {self.route_distance(chrom):.2f}, Fitness: {self.fitness(chrom):.4f}")
        
        for gen in range(1, self.num_generations + 1):
            self.next_generation()
            self.population.sort(key=cmp_to_key(self.compare_chromosomes))
            print(f"\nGeneración {gen}:")
            for idx, chrom in enumerate(self.population):
                dist = self.route_distance(chrom)
                fit = self.fitness(chrom)
                print(f"  Cromo {idx+1:2d}: {chrom}, Distancia: {dist:.2f}, Fitness: {fit:.4f}")
            best = self.population[0]
            print(f"-> Mejor ruta: {best}, Distancia: {self.route_distance(best):.2f}")
            
def run_tsp():
    # Construcción de la matriz de distancias:
    # Se utiliza una matriz 11x11 para poder indexar las ciudades de 1 a 10.
    M = 2 * np.ones((11, 11))
    # Se asignan distancias especiales (1) a determinadas aristas.
    M[1, 3] = 1; M[3, 5] = 1; M[5, 7] = 1; M[7, 9] = 1
    M[9, 2] = 1; M[2, 4] = 1; M[4, 6] = 1; M[6, 8] = 1; M[8, 10] = 1
    
    tsp_ga = TSP_GA(distance_matrix=M, num_cities=10, population_size=10,
                     mutation_probability=0.25, num_generations=200)
    tsp_ga.run()

if __name__ == "__main__":
    run_tsp()
