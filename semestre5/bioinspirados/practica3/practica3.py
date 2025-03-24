import numpy as np


def resolver_mochila(objetos, valores, pesos, capacidad):
    """
    Resuelve el problema de la mochila 0/1 usando programación dinámica.

    Parámetros:
      - objetos: secuencia de identificadores de los objetos.
      - valores: secuencia de valores correspondientes a cada objeto.
      - pesos: secuencia de pesos correspondientes a cada objeto.
      - capacidad: capacidad máxima de la mochila.

    Retorna:
      - valor_maximo: valor total óptimo alcanzado.
      - objetos_seleccionados: lista de objetos incluidos en la solución óptima.
      - dp: la matriz (tabla) de programación dinámica utilizada.
    """
    num_objetos = len(objetos)
    dp = np.zeros((num_objetos + 1, capacidad + 1), dtype=int)
    
    # Construcción de la tabla DP
    for i in range(1, num_objetos + 1):
        for cap in range(1, capacidad + 1):
            if pesos[i - 1] > cap:
                dp[i][cap] = dp[i - 1][cap]
            else:
                dp[i][cap] = max(dp[i - 1][cap],
                                 dp[i - 1][cap - pesos[i - 1]] + valores[i - 1])
    
    valor_maximo = dp[num_objetos][capacidad]
    
    # Recuperación de la solución (backtracking)
    objetos_seleccionados = []
    i, cap = num_objetos, capacidad
    while i > 0 and cap > 0:
        if dp[i][cap] != dp[i - 1][cap]:
            objetos_seleccionados.append(objetos[i - 1])
            cap -= pesos[i - 1]
        i -= 1

    return valor_maximo, objetos_seleccionados, dp


def resolver_cmp_minimo(denom, cantidad):
    """
    Resuelve el CMP para obtener el número mínimo de monedas necesarias para alcanzar
    una cantidad objetivo. Se supone que:
      i) Las denominaciones están en orden ascendente.
      ii) La primera denominación es 1.
      iii) Hay un número ilimitado de cada moneda.
    
    Parámetros:
      - denom: tuple o lista de denominaciones (ej. (1, 2, 5)).
      - cantidad: cantidad objetivo a alcanzar.

    Retorna:
      - min_coins: cantidad mínima de monedas.
      - dp: matriz (tabla) con los mínimos números de monedas.
      - monedas_usadas: lista de las monedas que se usaron en la solución (obtenida por backtracking).
    """
    n = len(denom)
    # Inicializamos la matriz DP de dimensiones n x (cantidad+1)
    dp = np.full((n, cantidad + 1), float('inf'))
    
    # Para cantidad 0 se necesitan 0 monedas
    for i in range(n):
        dp[i][0] = 0

    # Llenamos la primera fila (solo se puede usar la primera denominación)
    for col in range(1, cantidad + 1):
        if col % denom[0] == 0:
            dp[0][col] = col // denom[0]
        # Si no es divisible, queda como infinito (no alcanzable con solo la moneda 1, 
        # pero en nuestro caso la primera denominación es 1, así que siempre es divisible)

    # Llenamos el resto de la tabla
    for i in range(1, n):
        for col in range(1, cantidad + 1):
            if denom[i] > col:
                dp[i][col] = dp[i - 1][col]
            else:
                dp[i][col] = min(dp[i - 1][col],
                                 dp[i][col - denom[i]] + 1)
    
    min_coins = int(dp[n - 1][cantidad])
    
    # Backtracking para obtener las monedas utilizadas
    monedas_usadas = []
    i, col = n - 1, cantidad
    while col > 0 and i >= 0:
        if i == 0 or dp[i][col] != dp[i - 1][col]:
            monedas_usadas.append(denom[i])
            col -= denom[i]
        else:
            i -= 1

    return min_coins, dp, monedas_usadas


def resolver_cmp_combinaciones(denom, cantidad):
    """
    Resuelve el CMP para obtener, además del mínimo número de monedas, todas las combinaciones
    que permiten alcanzar la cantidad objetivo usando la cantidad mínima de monedas.

    Parámetros:
      - denom: tuple o lista de denominaciones (ej. (1, 3, 5)).
      - cantidad: cantidad objetivo a alcanzar.

    Retorna:
      - min_coins: cantidad mínima de monedas.
      - dp: matriz con el mínimo número de monedas (tipo entero).
      - combinaciones: estructura de combinaciones de monedas para cada subproblema.
    """
    n = len(denom)
    # Usamos float('inf') para inicializar, y luego convertiremos a int al final
    dp = np.full((n, cantidad + 1), float('inf'))
    # Estructura para almacenar combinaciones: para cada celda, lista de combinaciones
    combinaciones = [[[] for _ in range(cantidad + 1)] for _ in range(n)]
    
    # Base: cantidad 0 requiere 0 monedas y se representa con combinación vacía
    for i in range(n):
        dp[i][0] = 0
        combinaciones[i][0] = [[]]
    
    # Primera fila: solo se puede usar la primera denominación
    for col in range(1, cantidad + 1):
        if col % denom[0] == 0:
            dp[0][col] = col // denom[0]
            combinaciones[0][col] = [[denom[0]] * (col // denom[0])]
        else:
            # Se deja como vacío, ya que no es alcanzable con la única denominación
            combinaciones[0][col] = []
    
    # Llenado de la tabla para i >= 1
    for i in range(1, n):
        for col in range(1, cantidad + 1):
            # Opción 1: no usar la moneda actual
            sin_moneda = dp[i - 1][col]
            nuevas_combs = []
            
            # Opción 2: usar la moneda actual si es posible
            con_moneda = float('inf')
            if denom[i] <= col:
                con_moneda = dp[i][col - denom[i]] + 1
                if con_moneda < sin_moneda:
                    nuevas_combs = [comb + [denom[i]] for comb in combinaciones[i][col - denom[i]]]
                elif con_moneda == sin_moneda:
                    nuevas_combs = [comb + [denom[i]] for comb in combinaciones[i][col - denom[i]]]
            
            # Seleccionar la mejor opción
            if sin_moneda < con_moneda:
                dp[i][col] = sin_moneda
                combinaciones[i][col] = combinaciones[i - 1][col]
            elif sin_moneda > con_moneda:
                dp[i][col] = con_moneda
                combinaciones[i][col] = nuevas_combs
            else:
                dp[i][col] = sin_moneda  # que es igual a con_moneda
                # Unir ambas opciones evitando duplicados
                comb_set = {tuple(sorted(comb)) for comb in combinaciones[i - 1][col]}
                for comb in nuevas_combs:
                    comb_set.add(tuple(sorted(comb)))
                # Reconstruir la lista de combinaciones
                combinaciones[i][col] = [list(comb) for comb in comb_set]
    
    min_coins = int(dp[n - 1][cantidad])
    return min_coins, dp.astype(int), combinaciones[n - 1][cantidad]


if __name__ == "__main__":
    # ------------------------------
    # Problema de la Mochila - Ejemplos
    # ------------------------------
    print("=== Problema de la Mochila (Ejercicio 1) ===")
    objetos1 = (1, 2, 3)
    valores1 = (6, 10, 12)
    pesos1 = (1, 2, 3)
    capacidad1 = 5
    valor_max1, objs_selecc1, dp1 = resolver_mochila(objetos1, valores1, pesos1, capacidad1)
    print("Matriz de valores:")
    print(dp1)
    print("Valor máximo de la mochila:", valor_max1)
    print("Objetos en la mochila:", objs_selecc1)
    print("\n")
    
    print("=== Problema de la Mochila (Ejercicio 2) ===")
    objetos2 = (1, 2, 3, 4, 5)
    valores2 = (2, 3, 5, 5, 6)
    pesos2 = (2, 4, 4, 5, 7)
    capacidad2 = 9
    valor_max2, objs_selecc2, dp2 = resolver_mochila(objetos2, valores2, pesos2, capacidad2)
    print("Matriz de valores:")
    print(dp2)
    print("Valor máximo de la mochila:", valor_max2)
    print("Objetos en la mochila:", objs_selecc2)
    print("\n")
    
    # ------------------------------
    # Problema del CMP - Ejercicio 1: Mínimo número de monedas
    # ------------------------------
    print("=== CMP - Ejercicio 1 (Mínimo número de monedas) ===")
    denom1 = (1, 2, 5)
    cantidad1 = 7
    min_coins1, dp_cmp1, monedas_usadas1 = resolver_cmp_minimo(denom1, cantidad1)
    print("Matriz de valores:")
    print(dp_cmp1)
    print("Cantidad mínima de monedas:", min_coins1)
    print("Monedas utilizadas:", monedas_usadas1)
    print("\n")
    
    # ------------------------------
    # Problema del CMP - Ejercicio 2: Todas las combinaciones de monedas mínimas
    # ------------------------------
    print("=== CMP - Ejercicio 2 (Combinaciones de monedas) ===")
    denom2 = (1, 3, 5)
    cantidad2 = 6
    min_coins2, dp_cmp2, combs = resolver_cmp_combinaciones(denom2, cantidad2)
    print("Matriz de valores:")
    print(dp_cmp2)
    print("Cantidad mínima de monedas:", min_coins2)
    print("Combinaciones de monedas utilizadas:")
    for comb in combs:
        print(comb)
