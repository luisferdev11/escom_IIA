# Definir una lista con 100 números aleatorios de punto flotante entre -1000 y 1000. Sugerencia: usar numpy.
import numpy as np

lista = np.random.uniform(-1000, 1000, 100)
print(lista)

#Encontrar los dos número mayores/menores en la lista y reportarlos.
lista_ordenada = np.sort(lista)
mayores = lista_ordenada[-2:]
menores = lista_ordenada[:2]
print("Los dos números mayores son: ", mayores)
print("Los dos números menores son: ", menores)


# - Producir una lista con dos periodos de los valores de la función
#       f(t)=sin(2*pi*t/5 + 0.2).
# - Graficar los puntos (t,f(t))

import matplotlib.pyplot as plt

muestras = 10000
# El periodo de la función es 5 porque el argumento de la función seno es 2*pi*t/5 y el periodo del seno es 2*pi por lo que el periodo de la función es 5
t = np.linspace(0, 10, muestras)
f = np.sin(2*np.pi*t/5 + 0.2)
print(f)
plt.plot(t, f)
plt.show()

# - Encontrar los puntos donde la tangente a f(t) tiene pendiente cercana a cero y representarlos en la gráfica. Sugerencia: aproximar la tangente usando la secante.
pendientes = np.diff(f)/np.diff(t)
print("Las pendientes son ",pendientes)
tangentes = []
for i in range(len(pendientes)-1):
    # Si el producto de las pendientes de dos puntos consecutivos es negativo, entonces la tangente en ese punto es cercana a cero
    if pendientes[i]*pendientes[i+1] < 0:
        tangentes.append((t[i]+t[i+1])/2)



print(tangentes)
plt.plot(t, f)
plt.plot(tangentes, np.sin(2*np.pi*np.array(tangentes)/5 + 0.2), 'ro')
plt.show()