import numpy as np
import matplotlib.pyplot as plt
import sympy as sp
from typing import Any, Dict, List, Tuple, Union

# --------------------- Funciones Utilitarias ---------------------
def compute_gradient(f: sp.Expr, vars_list: List[sp.Symbol]) -> List[sp.Expr]:
    """Calcula el gradiente de la función simbólica f respecto a las variables en vars_list."""
    return [sp.diff(f, var) for var in vars_list]

def compute_hessian(f: sp.Expr, vars_list: List[sp.Symbol]) -> sp.Matrix:
    """Calcula la matriz Hessiana de la función simbólica f respecto a las variables en vars_list."""
    return sp.Matrix([[sp.diff(f, var1, var2) for var1 in vars_list] for var2 in vars_list])

def is_positive_definite(eigenvals: Union[Dict[Any, Any], List[float]]) -> bool:
    """
    Verifica si todos los valores propios (evaluados numéricamente) son positivos.
    Se intenta convertir cada valor a float; si falla o la conversión da un número <= 0,
    se considera que la matriz no es definida positiva.
    """
    # Extraer los valores propios en forma de lista
    if isinstance(eigenvals, dict):
        vals = list(eigenvals.keys())
    else:
        vals = eigenvals

    for val in vals:
        try:
            val_num = float(sp.N(val))
        except Exception:
            return False
        if val_num <= 0:
            return False
    return True


def print_hessian_analysis(f: sp.Expr, vars_list: List[sp.Symbol], crit_pt: Dict[sp.Symbol, Any]) -> bool:
    """
    Muestra el análisis de la Hessiana de f en el punto crítico crit_pt.
    Imprime la Hessiana simbólica, la matriz evaluada y sus valores propios.
    Retorna True si la Hessiana es definida positiva en ese punto (mínimo local), o False en caso contrario.
    """
    Hessian = compute_hessian(f, vars_list)
    print("Matriz Hessiana simbólica:")
    sp.pprint(Hessian)
    
    Hessian_eval = Hessian.subs(crit_pt)
    print("\nEvaluando la Hessiana en el punto crítico:")
    sp.pprint(crit_pt)
    print("Matriz Hessiana evaluada en el punto crítico:")
    sp.pprint(Hessian_eval)
    
    eigenvals = Hessian_eval.eigenvals()
    print("\nValores propios de la Hessiana evaluada:")
    sp.pprint(eigenvals)
    
    local_min = is_positive_definite(eigenvals)
    if local_min:
        print("\nLa Hessiana es definida positiva en este punto; se tiene un mínimo local.\n")
    else:
        print("\nLa Hessiana NO es definida positiva en este punto; no se garantiza un mínimo local.\n")
    return local_min

# --------------------- Problema 1 ---------------------
def analyze_f_sym() -> None:
    """
    Analiza la función f(x, y, z) = x² + y² + 7*z² - x*y:
      - Calcula el gradiente y resuelve gradiente = 0.
      - Para cada punto crítico determinado, muestra la Hessiana (simbólica y evaluada) y sus valores propios.
      - Se grafica una sección en z=0 para visualizar la función en ℝ².
      - Se imprime al final la lista de puntos críticos que son mínimos locales.
    """
    print("=== Análisis de f(x,y,z) = x² + y² + 7*z² - x*y ===")
    x, y, z = sp.symbols('x y z')
    f_sym = x**2 + y**2 + 7*z**2 - x*y
    vars_list = [x, y, z]

    # Calcular el gradiente y resolver gradiente = 0
    grad_f = compute_gradient(f_sym, vars_list)
    crit_solutions = sp.solve(grad_f, vars_list, dict=True)
    print("\nPunto(s) crítico(s) encontrado(s):")
    sp.pprint(crit_solutions)

    local_minima: List[Dict[sp.Symbol, Any]] = []
    # Analizar la Hessiana en cada punto crítico
    for sol in crit_solutions:
        print("\n--- Análisis Hessiano para el punto crítico ---")
        sp.pprint(sol)
        # Verificar si la solución está completamente determinada
        if any(val.free_symbols for val in sol.values()):
            print("Este punto crítico contiene parámetros libres; no se puede evaluar numéricamente la Hessiana completa.\n")
        else:
            if print_hessian_analysis(f_sym, vars_list, sol):
                local_minima.append(sol)

    print("Lista de puntos críticos que son mínimos locales en f(x,y,z):")
    sp.pprint(local_minima)

    # Visualización: Graficar la sección en z=0
    f_numeric = sp.lambdify((x, y, z), f_sym, 'numpy')
    x_vals = np.linspace(-5, 5, 400)
    y_vals = np.linspace(-5, 5, 400)
    X, Y = np.meshgrid(x_vals, y_vals)
    Z_section = f_numeric(X, Y, 0)

    # Suponiendo que el punto crítico proyectado en z=0 es el de la primera solución
    if crit_solutions:
        cp_xy: Tuple[float, float] = (float(crit_solutions[0][x]), float(crit_solutions[0][y]))
    else:
        cp_xy = (0.0, 0.0)

    plt.figure(figsize=(6, 5))
    CS = plt.contour(X, Y, Z_section, levels=30, cmap='viridis')
    plt.clabel(CS, inline=True, fontsize=8)
    plt.scatter(cp_xy[0], cp_xy[1], color='red', zorder=5, label=f'Punto crítico {cp_xy}')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Sección en z=0 de f(x,y,z)')
    plt.legend()
    plt.show()

# --------------------- Problema 2 ---------------------
def analyze_g_sym() -> None:
    """
    Analiza la función g(r,s,t,u) = r²*(s+1)² + t²*(u-1)⁴:
      - Calcula el gradiente y resuelve gradiente = 0.
      - Muestra cada solución encontrada. Si el punto crítico está completamente determinado (sin parámetros libres),
        se evalúa la Hessiana en ese punto y se comprueba la definitud; de lo contrario se indica que contiene parámetros libres.
      - Se muestran dos secciones para visualizar la función.
      - Se imprime la lista de puntos críticos que se pueden clasificar como mínimos locales.
    """
    print("=== Análisis de g(r,s,t,u) = r²*(s+1)² + t²*(u-1)⁴ ===")
    r, s, t, u = sp.symbols('r s t u')
    g_sym = r**2 * (s+1)**2 + t**2 * (u-1)**4
    vars_list = [r, s, t, u]

    # Calcular el gradiente y obtener las soluciones
    grad_g = compute_gradient(g_sym, vars_list)
    crit_solutions = sp.solve(grad_g, vars_list, dict=True)
    print("\nPunto(s) crítico(s) encontrado(s):")
    sp.pprint(crit_solutions)

    local_minima: List[Dict[sp.Symbol, Any]] = []
    # Para cada solución, se analiza la Hessiana si es completamente determinada
    for sol in crit_solutions:
        print("\n--- Análisis Hessiano para el punto crítico ---")
        sp.pprint(sol)
        if any(val.free_symbols for val in sol.values()):
            print("Este punto crítico contiene parámetros libres; no se puede evaluar numéricamente la Hessiana completa.\n")
        else:
            if print_hessian_analysis(g_sym, vars_list, sol):
                local_minima.append(sol)

    print("Lista de puntos críticos que son mínimos locales en g(r,s,t,u):")
    sp.pprint(local_minima)

    # Visualización: Se muestran dos secciones representativas
    # Sección 1: fijamos t=0, u=1 -> g(r,s,0,1) = r²*(s+1)²
    r_vals = np.linspace(-3, 3, 300)
    s_vals = np.linspace(-3, 3, 300)
    R, S = np.meshgrid(r_vals, s_vals)
    G1 = R**2 * (S+1)**2

    plt.figure(figsize=(6, 5))
    cs1 = plt.contourf(R, S, G1, levels=50, cmap='viridis')
    plt.colorbar(cs1)
    plt.scatter(0, -1, color='red', label='Mínimo: (r=0, s=-1)')
    plt.xlabel('r')
    plt.ylabel('s')
    plt.title('Sección: g(r,s,0,1) = r²*(s+1)²')
    plt.legend()
    plt.show()

    # Sección 2: fijamos r=0, s=-1 -> g(0,-1,t,u) = t²*(u-1)⁴
    t_vals = np.linspace(-3, 3, 300)
    u_vals = np.linspace(-3, 3, 300)
    T, U = np.meshgrid(t_vals, u_vals)
    G2 = T**2 * (U-1)**4

    plt.figure(figsize=(6, 5))
    cs2 = plt.contourf(T, U, G2, levels=50, cmap='plasma')
    plt.colorbar(cs2)
    plt.scatter(0, 1, color='red', label='Mínimo: (t=0, u=1)')
    plt.xlabel('t')
    plt.ylabel('u')
    plt.title('Sección: g(0,-1,t,u) = t²*(u-1)⁴')
    plt.legend()
    plt.show()

# --------------------- Problema 3 (Extra) ---------------------
def analyze_extra_function() -> None:
    """
    Analiza la función f(x,y) = x³ + 2*y³ - x*y:
      - Calcula sus puntos críticos y, para cada uno, muestra la Hessiana simbólica y evaluada,
        junto con sus valores propios.
      - Se indica si cada punto es mínimo local (Hessiana definida positiva) o no.
      - Se grafica en 3D la superficie de la función (el plano) y se resalta el punto mínimo local encontrado.
      - Al final se imprime la lista de puntos críticos que son mínimos locales.
    """
    print("=== Análisis de f(x,y) = x³ + 2*y³ - x*y ===")
    x, y = sp.symbols('x y')
    f_extra = x**3 + 2*y**3 - x*y
    vars_list = [x, y]

    # Calcular gradiente y obtener los puntos críticos
    grad_f = compute_gradient(f_extra, vars_list)
    crit_solutions = sp.solve(grad_f, vars_list, dict=True)
    print("\nPunto(s) crítico(s) encontrado(s):")
    sp.pprint(crit_solutions)

    local_minima: List[Dict[sp.Symbol, Any]] = []
    # Analizar la Hessiana para cada punto crítico
    for sol in crit_solutions:
        print("\n--- Análisis Hessiano para el punto crítico ---")
        sp.pprint(sol)
        if any(val.free_symbols for val in sol.values()):
            print("Este punto crítico contiene parámetros libres; no se puede evaluar numéricamente la Hessiana completa.\n")
        else:
            if print_hessian_analysis(f_extra, vars_list, sol):
                local_minima.append(sol)

    print("Lista de puntos críticos que son mínimos locales en f(x,y):")
    sp.pprint(local_minima)

    # Visualización 3D: Graficar la superficie de f(x,y) y marcar el mínimo local encontrado
    f_numeric = sp.lambdify((x, y), f_extra, 'numpy')
    x_vals = np.linspace(-3, 3, 400)
    y_vals = np.linspace(-3, 3, 400)
    X, Y = np.meshgrid(x_vals, y_vals)
    Z = f_numeric(X, Y)

    fig = plt.figure(figsize=(8, 6))
    ax = fig.add_subplot(111, projection='3d')
    surf = ax.plot_surface(X, Y, Z, cmap='viridis', edgecolor='none', alpha=0.8)
    fig.colorbar(surf, shrink=0.5, aspect=5)
    ax.set_xlabel('x')
    ax.set_ylabel('y')
    ax.set_zlabel('f(x,y)')
    ax.set_title('Superficie de f(x,y) y mínimo local')

    # Si se encontró al menos un mínimo local, se muestra el primer (o se pueden marcar todos)
    if local_minima:
        sol_min = local_minima[0]
        pt_min = (float(sol_min[x]), float(sol_min[y]), float(f_extra.subs(sol_min)))
        ax.scatter(pt_min[0], pt_min[1], pt_min[2], color='red', s=80, label=f'Mínimo local: {pt_min}')
        ax.legend()

    plt.show()



# --------------------- Función Principal ---------------------
def main() -> None:
    """Ejecuta el análisis de las tres funciones."""
    analyze_f_sym()
    analyze_g_sym()
    analyze_extra_function()

if __name__ == "__main__":
    main()
