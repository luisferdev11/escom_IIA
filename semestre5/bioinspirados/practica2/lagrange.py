import sympy as sp
import numpy as np
import matplotlib.pyplot as plt

# Definir variables simbólicas y el Lagrangiano para el problema
x, y, lam = sp.symbols('x y lam')
phi = (x-2)**2 + (y-2)**2   # Función a minimizar (distancia en el plano)
constraint = sp.Eq(x**2+y**2, 9)  # Restricción: x^2+y^2=9
L = phi - lam*(x**2+y**2-9)

# Calcular las derivadas parciales y resolver el sistema
eq1 = sp.diff(L, x)
eq2 = sp.diff(L, y)
eq3 = sp.diff(L, lam)

solutions = sp.solve([eq1, eq2, eq3], (x, y, lam), dict=True)
print("Soluciones (x,y,λ) para el problema 2.a:")
sp.pprint(solutions)

# Se evaluarán las distancias para elegir la mínima
distances = [phi.subs(sol) for sol in solutions]
print("Distancias al cuadrado en cada solución:")
sp.pprint(distances)

# Suponiendo que la solución con menor distancia es la óptima
opt_index = distances.index(min(distances))
opt_solution = solutions[opt_index]
print("Solución óptima:", opt_solution)

# --- Graficar el círculo y los puntos ---
theta = np.linspace(0, 2*np.pi, 400)
x_circle = 3 * np.cos(theta)
y_circle = 3 * np.sin(theta)

# Punto dado y solución óptima (en el plano z=0)
pt_given = np.array([2, 2])
pt_opt = np.array([float(opt_solution[x]), float(opt_solution[y])])

plt.figure(figsize=(6,5))
plt.plot(x_circle, y_circle, label='x²+y²=9')
plt.scatter(pt_given[0], pt_given[1], color='blue', label='Punto (2,2)')
plt.scatter(pt_opt[0], pt_opt[1], color='red', label='Óptimo')
plt.plot([pt_given[0], pt_opt[0]], [pt_given[1], pt_opt[1]], 'k--', label='Distancia mínima')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Optimización con restricción: Círculo x²+y²=9')
plt.legend()
plt.axis('equal')
plt.show()




# Definir variables simbólicas y el Lagrangiano para el problema 2.b
x, y, lam = sp.symbols('x y lam')
f_xy = x + y
constraint_eq = sp.Eq(x**2+y**2, 1)
L = f_xy - lam*(x**2+y**2-1)

# Condiciones de primer orden
eq1 = sp.diff(L, x)
eq2 = sp.diff(L, y)
eq3 = sp.diff(L, lam)

sol_lagrange = sp.solve([eq1, eq2, eq3], (x, y, lam), dict=True)
print("Soluciones para f(x,y)=x+y con restricción x²+y²=1:")
sp.pprint(sol_lagrange)

# Evaluar f(x,y) en cada solución para determinar máximo y mínimo
values = [f_xy.subs(sol) for sol in sol_lagrange]
print("Valores de f(x,y) en cada solución:")
sp.pprint(values)

# Asumimos que el máximo corresponde al mayor valor
max_index = values.index(max(values))
min_index = values.index(min(values))
sol_max = sol_lagrange[max_index]
sol_min = sol_lagrange[min_index]
print("Solución de máximo:", sol_max)
print("Solución de mínimo:", sol_min)

# --- Graficar el círculo y marcar los puntos ---
theta = np.linspace(0, 2*np.pi, 400)
x_unit = np.cos(theta)
y_unit = np.sin(theta)

pt_max = np.array([float(sol_max[x]), float(sol_max[y])])
pt_min = np.array([float(sol_min[x]), float(sol_min[y])])

plt.figure(figsize=(6,5))
plt.plot(x_unit, y_unit, label='x²+y²=1')
plt.scatter(pt_max[0], pt_max[1], color='red', label=f'Máximo: {pt_max}')
plt.scatter(pt_min[0], pt_min[1], color='green', label=f'Mínimo: {pt_min}')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Optimización de f(x,y)=x+y en el círculo unidad')
plt.legend()
plt.axis('equal')
plt.show()
