# Simulador de Autómatas Finitos No Deterministas (AFN)

Este programa permite cargar y simular Autómatas Finitos No Deterministas (AFN), incluyendo soporte para transiciones epsilon.

## Características

- Carga de AFN desde archivos de texto
- Soporte para transiciones epsilon
- Múltiples caminos de aceptación
- Visualización detallada de recorridos

## Compilación

Para compilar el programa, ejecute:

```bash
gcc -o practica4epsilon automata.c cadenas.c practica3.c
```

## Uso

Para ejecutar el programa:

```bash
./practica4epsilon archivo_automata.txt
```

Donde `archivo_automata.txt` es el archivo que contiene la definición del autómata.

## Formato del archivo de autómata

El archivo debe seguir el siguiente formato:

```
estado1,estado2,...,estadoN       # Lista de estados
simbolo1,simbolo2,...,simboloM    # Lista de símbolos del alfabeto (epsilon se incluye automáticamente)
estadoInicial                     # Estado inicial
estadoFinal1,estadoFinal2,...     # Lista de estados finales
origen1,simbolo1,destino1         # Transiciones (una por línea)
origen2,simbolo2,destino2
...
```

### Ejemplo:

```
0,1,2,3
a,b
0
3
0,a,1
0,epsilon,2
1,b,1
1,epsilon,2
2,a,2
2,b,3
3,a,3
3,b,3
```

## Notas importantes

- El símbolo "epsilon" se incluye automáticamente en el alfabeto, no es necesario añadirlo explícitamente.
- Las transiciones epsilon se especifican usando la palabra "epsilon" en lugar del símbolo.
- El programa muestra todos los posibles caminos de aceptación para una cadena.
