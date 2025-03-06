import numpy as np
import matplotlib.pyplot as plt
import sympy as sp

# Definir variables simbólicas y la función
x, y, z = sp.symbols('x y z')
f_sym = x**2 + y**2 + 7*z**2 - x*y

# Calcular el gradiente y resolver gradiente = 0
grad_f = [sp.diff(f_sym, var) for var in (x, y, z)]
critical_point = sp.solve(grad_f, (x, y, z))
print("Punto crítico para f(x,y,z):", critical_point)

# Calcular la matriz Hessiana
Hessian_f = sp.Matrix([[sp.diff(f_sym, var1, var2) for var1 in (x, y, z)] for var2 in (x, y, z)])
# Evaluar la Hessiana en el punto crítico obtenido
Hessian_at_cp = Hessian_f.subs(critical_point)
print("Hessiana evaluada en el punto crítico:")
sp.pprint(Hessian_at_cp)

# Calcular los valores propios de la Hessiana
eigenvals = Hessian_at_cp.eigenvals()
print("Valores propios de la Hessiana:")
sp.pprint(eigenvals)

# --- Gráfica de la función en la sección z=0 ---
# Usamos z=0 para la visualización en el plano (x,y)
def f_numeric(x, y, z):
    return x**2 + y**2 + 7*z**2 - x*y

x_vals = np.linspace(-5, 5, 400)
y_vals = np.linspace(-5, 5, 400)
X, Y = np.meshgrid(x_vals, y_vals)
Z_plane = f_numeric(X, Y, 0)

# Punto óptimo (en la sección z=0 el punto crítico es (0,0,0))
pt_opt = (critical_point[x], critical_point[y])
f_opt = f_numeric(pt_opt[0], pt_opt[1], 0)

plt.figure(figsize=(6,5))
CS = plt.contour(X, Y, Z_plane, levels=30, cmap='viridis')
plt.clabel(CS, inline=True, fontsize=8)
plt.scatter(pt_opt[0], pt_opt[1], color='red', zorder=5, label='Punto crítico (0,0)')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Sección z=0: f(x,y,0) = x²+y² - xy')
plt.legend()
plt.show()





# Definir variables simbólicas y la función g
r, s, t, u = sp.symbols('r s t u')
g_sym = r**2 * (s+1)**2 + t**2 * (u-1)**4

# Calcular el gradiente y resolver
grad_g = [sp.diff(g_sym, var) for var in (r, s, t, u)]
critical_points_g = sp.solve(grad_g, (r, s, t, u), dict=True)
print("Puntos críticos para g(r,s,t,u):")
sp.pprint(critical_points_g)

# --- Graficar dos secciones ---
# Sección 1: fijamos t=0, u=1 para graficar g(r,s,0,1) = r^2*(s+1)^2
r_vals = np.linspace(-3, 3, 300)
s_vals = np.linspace(-3, 3, 300)
R, S = np.meshgrid(r_vals, s_vals)
G1 = R**2 * (S+1)**2

plt.figure(figsize=(6,5))
cs1 = plt.contourf(R, S, G1, levels=50, cmap='viridis')
plt.colorbar(cs1)
plt.scatter(0, -1, color='red', label='Mínimo (r=0, s=-1)')
plt.xlabel('r')
plt.ylabel('s')
plt.title('Sección: g(r,s,0,1) = r²*(s+1)²')
plt.legend()
plt.show()

# Sección 2: fijamos r=0, s=-1 para graficar g(0,-1,t,u) = t^2*(u-1)^4
t_vals = np.linspace(-3, 3, 300)
u_vals = np.linspace(-3, 3, 300)
T, U = np.meshgrid(t_vals, u_vals)
G2 = T**2 * (U-1)**4

plt.figure(figsize=(6,5))
cs2 = plt.contourf(T, U, G2, levels=50, cmap='plasma')
plt.colorbar(cs2)
plt.scatter(0, 1, color='red', label='Mínimo (t=0, u=1)')
plt.xlabel('t')
plt.ylabel('u')
plt.title('Sección: g(0,-1,t,u) = t²*(u-1)⁴')
plt.legend()
plt.show()
