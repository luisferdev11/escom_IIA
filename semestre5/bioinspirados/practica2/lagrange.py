import sympy as sp
import numpy as np
import matplotlib.pyplot as plt
from typing import List, Dict, Any

def solve_lagrange(function: sp.Expr, 
                    constraint: sp.Eq, 
                    variables: List[sp.Symbol], 
                    lam: sp.Symbol) -> List[Dict[Any, Any]]:
    """
    Resuelve el método de los multiplicadores de Lagrange para la función 'function'
    y la restricción 'constraint' en las variables indicadas.
    
    Se define el Lagrangiano:
        L = function - lam*(g)
    donde g se obtiene de constraint.lhs - constraint.rhs.
    """
    g_expr = constraint.lhs - constraint.rhs
    L = function - lam * g_expr
    eqs = [sp.diff(L, var) for var in variables] + [sp.diff(L, lam)]
    solutions = sp.solve(eqs, variables + [lam], dict=True)
    return solutions

def problem_2a() -> None:
    """
    Problema 2.a:
      - Minimizar la distancia entre el punto P(2,2,2) y un punto (x,y,0) sobre el círculo x²+y²=9.
      - Se minimiza la función phi = (x-2)²+(y-2)² (la parte variable de la distancia al ignorar la componente z constante).
      - La distancia real se calcula como: sqrt( (x-2)²+(y-2)² + (0-2)² ).
      - Se grafica en 3D el círculo (en el plano z=0), el punto P y el punto óptimo.
    """
    # Definición de variables simbólicas
    x, y, lam = sp.symbols('x y lam')
    # Función a minimizar (solo la parte en x e y)
    phi = (x - 2)**2 + (y - 2)**2  
    # Restricción: círculo x²+y²=9
    constraint = sp.Eq(x**2 + y**2, 9)
    
    # Resolver el problema de Lagrange
    solutions = solve_lagrange(phi, constraint, [x, y], lam)
    print("=== Problema 2.a: Minimización de la distancia ===")
    print("Soluciones (x, y, λ) encontradas:")
    sp.pprint(solutions)
    
    # Evaluación de la función objetivo en cada solución
    phi_values = [phi.subs(sol) for sol in solutions]
    print("\nValores de (x-2)²+(y-2)² en cada solución:")
    sp.pprint(phi_values)
    
    # Seleccionar la solución que minimiza la distancia (en el plano xy)
    min_index = phi_values.index(min(phi_values))
    opt_solution = solutions[min_index]
    print("\nSolución óptima (minimiza la distancia en el plano xy):")
    sp.pprint(opt_solution)
    
    # Calcular la distancia real incluyendo la diferencia en z (la componente fija es 2 en z)
    opt_phi = float(phi.subs(opt_solution))
    distance = np.sqrt(opt_phi + 4)  # (0-2)² = 4
    print(f"\nDistancia real mínima desde P(2,2,2) al punto óptimo del círculo: {distance:.4f}")
    
    # Preparar datos para el gráfico 3D
    theta = np.linspace(0, 2 * np.pi, 400)
    x_circle = 3 * np.cos(theta)
    y_circle = 3 * np.sin(theta)
    z_circle = np.zeros_like(theta)  # El círculo está en z=0
    
    pt_given = np.array([2, 2, 2])
    pt_opt = np.array([float(opt_solution[x]), float(opt_solution[y]), 0])
    
    fig = plt.figure(figsize=(8, 6))
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(x_circle, y_circle, z_circle, label='Círculo: x²+y²=9')
    ax.scatter(pt_given[0], pt_given[1], pt_given[2], color='blue', s=50, label='Punto P(2,2,2)')
    ax.scatter(pt_opt[0], pt_opt[1], pt_opt[2], color='red', s=50, label='Punto óptimo sobre el círculo')
    # Dibujar la línea de la distancia mínima
    ax.plot([pt_opt[0], pt_given[0]], [pt_opt[1], pt_given[1]], [pt_opt[2], pt_given[2]], 'k--', label='Trayecto mínimo')
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('z')
    ax.set_title('Problema 2.a: Minimización de la distancia (Gráfico 3D)')
    ax.legend()
    plt.show()

def problem_2b() -> None:
    """
    Problema 2.b:
      - Optimizar la función f(x,y) = x + y sobre el círculo unidad x²+y²=1.
      - Se identifican las soluciones que maximizan y minimizan f(x,y).
      - Se grafica el círculo junto con los puntos correspondientes.
    """
    # Definición de variables simbólicas
    x, y, lam = sp.symbols('x y lam')
    f_xy = x + y
    constraint = sp.Eq(x**2 + y**2, 1)
    
    # Resolver el problema de Lagrange
    solutions = solve_lagrange(f_xy, constraint, [x, y], lam)
    print("=== Problema 2.b: Optimización de f(x,y)=x+y ===")
    print("Soluciones (x, y, λ) encontradas:")
    sp.pprint(solutions)
    
    # Evaluar f(x,y) en cada solución
    f_values = [f_xy.subs(sol) for sol in solutions]
    print("\nValores de f(x,y) en cada solución:")
    sp.pprint(f_values)
    
    # Determinar la solución de máximo y de mínimo
    max_index = f_values.index(max(f_values))
    min_index = f_values.index(min(f_values))
    sol_max = solutions[max_index]
    sol_min = solutions[min_index]
    print("\nSolución que maximiza f(x,y):")
    sp.pprint(sol_max)
    print("\nSolución que minimiza f(x,y):")
    sp.pprint(sol_min)
    
    # Preparar el gráfico 2D: círculo unidad
    theta = np.linspace(0, 2 * np.pi, 400)
    x_circle = np.cos(theta)
    y_circle = np.sin(theta)
    
    pt_max = np.array([float(sol_max[x]), float(sol_max[y])])
    pt_min = np.array([float(sol_min[x]), float(sol_min[y])])
    
    plt.figure(figsize=(6, 5))
    plt.plot(x_circle, y_circle, label='Círculo unidad: x²+y²=1')
    plt.scatter(pt_max[0], pt_max[1], color='red', label=f'Máximo: {pt_max}')
    plt.scatter(pt_min[0], pt_min[1], color='green', label=f'Mínimo: {pt_min}')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Problema 2.b: Optimización de f(x,y)=x+y en el círculo unidad')
    plt.legend()
    plt.axis('equal')
    plt.show()

def problem_additional() -> None:
    """
    Problema adicional:
      - Optimizar la función f(x,y)=9 - x² - y² con la restricción x+y=3.
      - Se resuelve el problema mediante multiplicadores de Lagrange.
      - Se grafica en 3D la superficie f(x,y)=9 - x² - y², la línea de restricción x+y=3 
        (obtenida evaluando f en los puntos de la restricción) y se marca el punto óptimo.
    """
    # Definición de variables simbólicas
    x, y, lam = sp.symbols('x y lam')
    f_xy = 9 - x**2 - y**2
    constraint = sp.Eq(x + y, 3)
    
    # Resolver el problema de Lagrange
    solutions = solve_lagrange(f_xy, constraint, [x, y], lam)
    print("=== Problema Adicional: Optimización de f(x,y)=9 - x² - y² ===")
    print("Soluciones (x, y, λ) encontradas:")
    sp.pprint(solutions)
    
    # Evaluar f(x,y) en cada solución
    f_values = [f_xy.subs(sol) for sol in solutions]
    print("\nValores de f(x,y) en cada solución:")
    sp.pprint(f_values)
    
    # Se espera una única solución: x = y = 3/2
    opt_solution = solutions[0] if solutions else {}
    print("\nSolución óptima:")
    sp.pprint(opt_solution)
    
    # Preparar la gráfica 3D de la superficie f(x,y)
    fig = plt.figure(figsize=(10, 8))
    ax = fig.add_subplot(111, projection='3d')
    
    # Definir un rango de valores para x y y para la superficie
    x_vals = np.linspace(-3, 3, 100)
    y_vals = np.linspace(-3, 3, 100)
    X, Y = np.meshgrid(x_vals, y_vals)
    Z = 9 - X**2 - Y**2  # f(x,y)
    
    # Graficar la superficie
    surf = ax.plot_surface(X, Y, Z, alpha=0.7, cmap='viridis', edgecolor='none')
    fig.colorbar(surf, shrink=0.5, aspect=5, label='f(x,y)')
    
    # Graficar la línea de restricción: x+y=3
    # Usamos un parámetro t para x y obtenemos y = 3 - t
    t_vals = np.linspace(-1, 4, 400)
    x_line = t_vals
    y_line = 3 - t_vals
    z_line = 9 - np.array(x_line)**2 - np.array(y_line)**2  # Evaluar la función en la restricción
    
    ax.plot(x_line, y_line, z_line, 'r-', linewidth=3, label='Restricción: x+y=3')
    
    # Graficar el punto óptimo sobre la superficie
    pt_opt = np.array([float(opt_solution[x]), float(opt_solution[y]), float(f_xy.subs(opt_solution))])
    ax.scatter(pt_opt[0], pt_opt[1], pt_opt[2], color='black', s=80, label=f'Óptimo: {pt_opt}')
    
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('f(x,y)')
    ax.set_title('Problema Adicional: f(x,y)=9-x²-y² con restricción x+y=3')
    ax.legend()
    plt.show()



def main() -> None:
    """
    Función principal que ejecuta los tres problemas.
    """
    problem_2a()
    problem_2b()
    problem_additional()

if __name__ == "__main__":
    main()
