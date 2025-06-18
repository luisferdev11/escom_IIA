import argparse
import logging
import sys
import time
from typing import Tuple, List

import numpy as np
import matplotlib.pyplot as plt


def schwefel(x: np.ndarray) -> float:
    """
    Schwefel function for optimization. Global minimum at x_i = 420.9687, f(x) = 0.

    Parameters:
        x (np.ndarray): Input vector of shape (n_dimensions,).

    Returns:
        float: Function value.
    """
    dim = x.size
    return 418.9829 * dim - np.sum(x * np.sin(np.sqrt(np.abs(x))))


class ParticleSwarmOptimizer:
    def __init__(
        self,
        func,
        n_particles: int = 30,
        n_dimensions: int = 4,
        bounds: Tuple[float, float] = (-500.0, 500.0),
        max_iter: int = 300,
        inertia: float = 0.7298,
        cognitive: float = 1.49618,
        social: float = 1.49618,
        seed: int = None,
    ):
        self.func = func
        self.n_particles = n_particles
        self.n_dimensions = n_dimensions
        self.lower, self.upper = bounds
        self.max_iter = max_iter
        self.w = inertia
        self.c1 = cognitive
        self.c2 = social
        self.params = {
            "n_particles": n_particles, "n_dimensions": n_dimensions, "bounds": bounds,
            "max_iter": max_iter, "inertia": inertia, "cognitive": cognitive,
            "social": social, "seed": seed
        }

        if seed is not None:
            np.random.seed(seed)

        self.X = np.random.uniform(
            self.lower, self.upper, (n_particles, n_dimensions)
        )
        vel_bound = self.upper - self.lower
        self.V = np.random.uniform(-vel_bound, vel_bound, (n_particles, n_dimensions)) * 0.1

        fitness = np.apply_along_axis(self.func, 1, self.X)
        self.pbest = self.X.copy()
        self.pbest_val = fitness.copy()
        g_idx = np.argmin(self.pbest_val)
        self.gbest = self.pbest[g_idx].copy()
        self.gbest_val = self.pbest_val[g_idx]
        
        self.gbest_history = [] # For storing gbest_val at each iteration

    def optimize(self) -> Tuple[np.ndarray, float, List[float]]:
        self.gbest_history.append(self.gbest_val) # Store initial best

        for i in range(1, self.max_iter + 1):
            r1 = np.random.rand(self.n_particles, self.n_dimensions)
            r2 = np.random.rand(self.n_particles, self.n_dimensions)

            self.V = (
                self.w * self.V
                + self.c1 * r1 * (self.pbest - self.X)
                + self.c2 * r2 * (self.gbest - self.X)
            )
            self.X += self.V
            np.clip(self.X, self.lower, self.upper, out=self.X)

            fitness = np.apply_along_axis(self.func, 1, self.X)
            improved = fitness < self.pbest_val
            self.pbest[improved] = self.X[improved]
            self.pbest_val[improved] = fitness[improved]

            current_best_iter_val = np.min(self.pbest_val)
            if current_best_iter_val < self.gbest_val:
                idx = np.argmin(self.pbest_val)
                self.gbest_val = current_best_iter_val
                self.gbest = self.pbest[idx].copy()

            self.gbest_history.append(self.gbest_val)
            logging.debug(f"PSO Iteration {i:03d}: gbest_val={self.gbest_val:.4f}")

        return self.gbest, self.gbest_val, self.gbest_history


class GeneticAlgorithmOptimizer:
    def __init__(
        self,
        func,
        pop_size: int = 35,
        n_dimensions: int = 4,
        bounds: Tuple[float, float] = (-500.0, 500.0),
        max_gen: int = 300,
        crossover_rate: float = 0.9,
        mutation_rate: float = 0.19, # increased slightly for more exploration
        mutation_scale: float = 0.1,
        tournament_size: int = 3,
        seed: int = None,
    ):
        self.func = func
        self.pop_size = pop_size
        self.n_dimensions = n_dimensions
        self.lower, self.upper = bounds
        self.max_gen = max_gen
        self.cr = crossover_rate
        self.mr = mutation_rate
        self.ms = mutation_scale
        self.ts = tournament_size
        self.params = {
            "pop_size": pop_size, "n_dimensions": n_dimensions, "bounds": bounds,
            "max_gen": max_gen, "crossover_rate": crossover_rate,
            "mutation_rate": mutation_rate, "mutation_scale": mutation_scale,
            "tournament_size": tournament_size, "seed": seed
        }

        if seed is not None:
            np.random.seed(seed)

        self.population = np.random.uniform(
            self.lower, self.upper, (pop_size, n_dimensions)
        )
        self.fitness = np.apply_along_axis(self.func, 1, self.population)
        self.best_fitness_history = [] # For storing best fitness at each generation

    def tournament_selection(self) -> np.ndarray:
        idx = np.random.choice(self.pop_size, self.ts, replace=False)
        return self.population[idx[np.argmin(self.fitness[idx])]]

    def crossover(self, parent1: np.ndarray, parent2: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
        if np.random.rand() < self.cr:
            alpha = 0.5
            # BLX-alpha
            low = np.minimum(parent1, parent2) - alpha * np.abs(parent1 - parent2)
            high = np.maximum(parent1, parent2) + alpha * np.abs(parent1 - parent2)
            
            child1 = np.random.uniform(low, high, self.n_dimensions)
            child2 = np.random.uniform(low, high, self.n_dimensions)
            
            np.clip(child1, self.lower, self.upper, out=child1)
            np.clip(child2, self.lower, self.upper, out=child2)
            return child1, child2
        return parent1.copy(), parent2.copy()


    def mutate(self, individual: np.ndarray) -> np.ndarray:
        for i in range(self.n_dimensions):
            if np.random.rand() < self.mr: # Per-gene mutation probability
                noise = np.random.normal(0, self.ms * (self.upper - self.lower))
                individual[i] += noise
        np.clip(individual, self.lower, self.upper, out=individual)
        return individual

    def optimize(self) -> Tuple[np.ndarray, float, List[float]]:
        self.best_fitness_history.append(np.min(self.fitness)) # Store initial best

        for gen in range(1, self.max_gen + 1):
            new_pop = []
            best_idx = np.argmin(self.fitness)
            new_pop.append(self.population[best_idx].copy()) # Elitism

            while len(new_pop) < self.pop_size:
                p1 = self.tournament_selection()
                p2 = self.tournament_selection()
                c1, c2 = self.crossover(p1, p2)
                new_pop.append(self.mutate(c1))
                if len(new_pop) < self.pop_size:
                    new_pop.append(self.mutate(c2))
            
            self.population = np.vstack(new_pop)
            self.fitness = np.apply_along_axis(self.func, 1, self.population)
            
            current_best_gen_val = np.min(self.fitness)
            self.best_fitness_history.append(current_best_gen_val)
            logging.debug(f"GA Generation {gen:03d}: best={current_best_gen_val:.4f}")

        best_idx = np.argmin(self.fitness)
        return self.population[best_idx], self.fitness[best_idx], self.best_fitness_history


def plot_convergence(pso_history: List[float], ga_history: List[float], title: str = "Convergence Plot"):
    """Plots the convergence of PSO and GA."""
    plt.figure(figsize=(10, 6))
    plt.plot(pso_history, label="PSO Best Fitness", color="blue")
    plt.plot(ga_history, label="GA Best Fitness", color="red")
    plt.xlabel("Iteration / Generation")
    plt.ylabel("Best Fitness Value")
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.show()

def plot_solutions_2d(pso_sol: np.ndarray, ga_sol: np.ndarray, 
                      optimum_pos: np.ndarray, bounds: Tuple[float, float],
                      title: str = "Final Solutions (2D)"):
    """Plots the final solutions if 2D, along with the known optimum."""
    if pso_sol.size != 2 or ga_sol.size != 2 or optimum_pos.size != 2:
        logging.info("Solution plot is only available for 2D problems.")
        return

    plt.figure(figsize=(8, 8))
    # Plot solutions
    plt.scatter(pso_sol[0], pso_sol[1], marker='X', color='blue', s=150, label=f'PSO Sol ({pso_sol[0]:.2f}, {pso_sol[1]:.2f})', zorder=5)
    plt.scatter(ga_sol[0], ga_sol[1], marker='P', color='red', s=150, label=f'GA Sol ({ga_sol[0]:.2f}, {ga_sol[1]:.2f})', zorder=5)
    plt.scatter(optimum_pos[0], optimum_pos[1], marker='*', color='gold', s=200, label=f'Global Optimum ({optimum_pos[0]:.2f}, {optimum_pos[1]:.2f})', zorder=4, edgecolors='black')

    # Contour plot for Schwefel function (optional, can be slow for high res)
    x_ = np.linspace(bounds[0], bounds[1], 100)
    y_ = np.linspace(bounds[0], bounds[1], 100)
    X_grid, Y_grid = np.meshgrid(x_, y_)
    Z_grid = np.zeros_like(X_grid)
    for i in range(X_grid.shape[0]):
        for j in range(X_grid.shape[1]):
            Z_grid[i, j] = schwefel(np.array([X_grid[i, j], Y_grid[i, j]]))
    
    plt.contourf(X_grid, Y_grid, Z_grid, levels=50, cmap='viridis', alpha=0.7)
    plt.colorbar(label='Schwefel Function Value')
    
    plt.xlim(bounds[0], bounds[1])
    plt.ylim(bounds[0], bounds[1])
    plt.xlabel("x1")
    plt.ylabel("x2")
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.axhline(0, color='black', linewidth=0.5)
    plt.axvline(0, color='black', linewidth=0.5)
    plt.gca().set_aspect('equal', adjustable='box')
    plt.tight_layout()
    plt.show()


def main():
    logging.basicConfig(level=logging.INFO, format="%(levelname)s: %(message)s") # Changed format
    parser = argparse.ArgumentParser(description="Compare PSO and GA on Schwefel function.")
    parser.add_argument("--seed", type=int, default=None, help="Random seed.")
    parser.add_argument("--dims", type=int, default=2, help="Number of dimensions for the Schwefel function.") # Changed to 2 for plotting
    parser.add_argument("--particles", type=int, default=30, help="Number of particles (PSO) / Population size (GA).")
    parser.add_argument("--iters", type=int, default=30, help="Max iterations (PSO) / Max generations (GA).") # Reduced for faster example
    args = parser.parse_args()

    N_DIMENSIONS = args.dims
    POP_SIZE = args.particles # Use same for both for this comparison
    MAX_ITER_GEN = args.iters
    BOUNDS = (-500.0, 500.0)
    SCHWEFEL_OPTIMUM_POS = np.full(N_DIMENSIONS, 420.9687)
    SCHWEFEL_OPTIMUM_VAL = 0.0

    logging.info(f"Running Schwefel function optimization with {N_DIMENSIONS} dimensions.")
    logging.info(f"Known global optimum: f(x) = {SCHWEFEL_OPTIMUM_VAL} at x_i = {SCHWEFEL_OPTIMUM_POS[0]:.4f}\n")

    # --- PSO ---
    logging.info("--- Particle Swarm Optimization (PSO) ---")
    pso = ParticleSwarmOptimizer(func=schwefel, 
                                 n_particles=POP_SIZE, 
                                 n_dimensions=N_DIMENSIONS, 
                                 bounds=BOUNDS, 
                                 max_iter=MAX_ITER_GEN, 
                                 seed=args.seed)
    logging.info(f"Parameters: {pso.params}")
    
    start_time = time.time()
    pso_sol, pso_val, pso_history = pso.optimize()
    pso_time = time.time() - start_time
    
    pso_nfe = pso.n_particles * (pso.max_iter + 1) # +1 for initial evaluation
    pso_dist_opt = np.linalg.norm(pso_sol - SCHWEFEL_OPTIMUM_POS)

    logging.info(f"PSO Execution Time: {pso_time:.4f}s")
    logging.info(f"PSO NFE (approx): {pso_nfe}")
    logging.info(f"PSO Best Solution: {pso_sol.round(4)}")
    logging.info(f"PSO Fitness: {pso_val:.4f}")
    logging.info(f"PSO Distance to Optimum: {pso_dist_opt:.4f}\n")

    # --- GA ---
    logging.info("--- Genetic Algorithm (GA) ---")
    ga = GeneticAlgorithmOptimizer(func=schwefel, 
                                   pop_size=POP_SIZE, 
                                   n_dimensions=N_DIMENSIONS, 
                                   bounds=BOUNDS, 
                                   max_gen=MAX_ITER_GEN, 
                                   seed=args.seed) # Use same seed for fair comparison
    logging.info(f"Parameters: {ga.params}")
    
    start_time = time.time()
    ga_sol, ga_val, ga_history = ga.optimize()
    ga_time = time.time() - start_time

    # NFE for GA: initial pop + (pop_size-1 new individuals if elitism) * generations
    # Current code re-evaluates the whole new population: pop_size (initial) + pop_size * max_gen
    ga_nfe = ga.pop_size * (ga.max_gen + 1)
    ga_dist_opt = np.linalg.norm(ga_sol - SCHWEFEL_OPTIMUM_POS)

    logging.info(f"GA Execution Time: {ga_time:.4f}s")
    logging.info(f"GA NFE (approx): {ga_nfe}")
    logging.info(f"GA Best Solution: {ga_sol.round(4)}")
    logging.info(f"GA Fitness: {ga_val:.4f}")
    logging.info(f"GA Distance to Optimum: {ga_dist_opt:.4f}\n")

    # --- Comparison Summary ---
    logging.info("--- Comparison Summary ---")
    logging.info(f"Execution Times: PSO={pso_time:.4f}s, GA={ga_time:.4f}s")
    logging.info(f"NFE (approx): PSO={pso_nfe}, GA={ga_nfe}")
    logging.info(f"Final Fitness: PSO={pso_val:.4f}, GA={ga_val:.4f}")
    logging.info(f"Distance to Optimum: PSO={pso_dist_opt:.4f}, GA={ga_dist_opt:.4f}")

    # --- Plotting ---
    plot_convergence(pso_history, ga_history, title=f"Convergence on Schwefel ({N_DIMENSIONS}D)")
    if N_DIMENSIONS == 2:
        plot_solutions_2d(pso_sol, ga_sol, SCHWEFEL_OPTIMUM_POS, BOUNDS, 
                          title=f"Final Solutions on Schwefel ({N_DIMENSIONS}D)")
    elif N_DIMENSIONS == 3:
        logging.warning("3D solution plotting not implemented in this example. Consider libraries like Plotly for interactive 3D scatter plots.")
        # You could add a basic 3D scatter plot here using mplot3d if desired
        # from mpl_toolkits.mplot3d import Axes3D
        # fig = plt.figure()
        # ax = fig.add_subplot(111, projection='3d')
        # ax.scatter(SCHWEFEL_OPTIMUM_POS[0], SCHWEFEL_OPTIMUM_POS[1], SCHWEFEL_OPTIMUM_POS[2], c='gold', marker='*', s=200, label='Optimum')
        # ax.scatter(pso_sol[0], pso_sol[1], pso_sol[2], c='blue', marker='X', s=150, label='PSO')
        # ax.scatter(ga_sol[0], ga_sol[1], ga_sol[2], c='red', marker='P', s=150, label='GA')
        # ax.set_xlabel('X'); ax.set_ylabel('Y'); ax.set_zlabel('Z')
        # ax.legend()
        # plt.show()

if __name__ == "__main__":
    main()