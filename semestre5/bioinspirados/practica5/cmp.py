import random

class CMP_GA:
    def __init__(self, target_value=6, valid_objects=[1, 3, 5],
                 population_size=10, initial_length=1,
                 mutation_probability=0.75, max_generations=20):
        self.target_value = target_value
        self.valid_objects = valid_objects
        self.population_size = population_size
        self.chromosome_length = initial_length  # Longitud actual de los cromosomas.
        self.mutation_probability = mutation_probability
        self.max_generations = max_generations
        self.population = [self.random_chromosome() for _ in range(population_size)]
        
    def random_chromosome(self):
        """
        Genera un cromosoma aleatorio de longitud 'chromosome_length'.
        """
        return [random.choice(self.valid_objects) for _ in range(self.chromosome_length)]
        
    def fitness(self, chromosome):
        """
        Calcula el fitness usando la fórmula 1/(1+error) donde error = |suma - target_value|.
        """
        error = abs(sum(chromosome) - self.target_value)
        return 1 / (1 + error)
        
    def print_chromosome_info(self, idx, chromosome):
        """
        Muestra la información del cromosoma: contenido, suma y fitness.
        """
        s = sum(chromosome)
        fit = self.fitness(chromosome)
        print(f"  Cromo {idx+1:2d}: {chromosome}, Suma: {s:2d}, Fitness: {fit:.4f}")
    
    def crossover(self, parent1, parent2):
        """
        Cruce de un punto.
        Si la longitud es 1, se retorna una copia de parent1.
        """
        if self.chromosome_length == 1:
            return parent1.copy()
        point = random.randint(1, self.chromosome_length - 1)
        return parent1[:point] + parent2[point:]
    
    def mutate(self, chromosome):
        """
        Mutación por intercambio de un objeto aleatorio.
        Se elige un índice aleatorio y se reemplaza el objeto en esa posición por otro aleatorio.
        """
        idx = random.randint(0, self.chromosome_length - 1)
        new_value = random.choice(self.valid_objects)
        chromosome[idx] = new_value
        return chromosome
        
    def next_generation(self):
        """
        Genera la siguiente generación mediante selección ponderada y elitismo.
        """
        # Ordena la población de mayor a menor fitness.
        self.population.sort(key=lambda chrom: self.fitness(chrom), reverse=True)
        new_population = self.population[:2]  # Elitismo: conservar los dos mejores.
        
        while len(new_population) < self.population_size:
            # Selección ponderada según fitness.
            weights = [self.fitness(chrom) for chrom in self.population]
            parent1, parent2 = random.choices(self.population, weights=weights, k=2)
            # Cruza para generar dos hijos.
            child1 = self.crossover(parent1, parent2)
            child2 = self.crossover(parent2, parent1)
            # Mutación con probabilidad.
            if random.random() < self.mutation_probability:
                child1 = self.mutate(child1)
            if random.random() < self.mutation_probability:
                child2 = self.mutate(child2)
            new_population.append(child1)
            if len(new_population) < self.population_size:
                new_population.append(child2)
        self.population = new_population

    def increase_chromosome_length(self):
        """
        Incrementa la longitud de los cromosomas agregando un nuevo objeto aleatorio a cada uno.
        """
        self.chromosome_length += 1
        self.population = [chrom + [random.choice(self.valid_objects)]
                           for chrom in self.population]

    def run(self):
        """
        Ejecuta el ciclo evolutivo hasta alcanzar la solución o el máximo de generaciones.
        """
        print("Algoritmo Genético para resolver el problema CMP (target = {})".format(self.target_value))
        print(f"Objetos disponibles: {self.valid_objects}")
        print(f"Tamaño inicial de cromosoma: {self.chromosome_length}\n")
        
        generation = 0
        solution_found = False
        
        while generation < self.max_generations and not solution_found:
            print(f"--- Generación {generation+1} (Longitud = {self.chromosome_length}) ---")
            for idx, chrom in enumerate(self.population):
                self.print_chromosome_info(idx, chrom)
            self.population.sort(key=lambda chrom: self.fitness(chrom), reverse=True)
            best = self.population[0]
            best_sum = sum(best)
            if best_sum == self.target_value:
                print("\n¡Solución encontrada!")
                self.print_chromosome_info(0, best)
                solution_found = True
                break
            if best_sum < self.target_value:
                print(f"\nEl mejor cromosoma tiene suma {best_sum} (menos que target {self.target_value}).")
                print("Incrementando la longitud de los cromosomas para intentar llegar al target.\n")
                self.increase_chromosome_length()
            self.next_generation()
            generation += 1
        
        if not solution_found:
            print("\nNo se encontró solución exacta en las generaciones ejecutadas.")
            self.population.sort(key=lambda chrom: self.fitness(chrom), reverse=True)
            print("Mejor solución final:")
            self.print_chromosome_info(0, self.population[0])

def run_cmp():
    cmp_ga = CMP_GA()
    cmp_ga.run()

if __name__ == "__main__":
    run_cmp()
