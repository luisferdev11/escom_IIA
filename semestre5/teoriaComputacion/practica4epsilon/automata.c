#include "automata.h"

// Función auxiliar para crear un nodo de transición
static NodoTransicion *crearNodoTransicion(int destino) {
    NodoTransicion *nuevo = (NodoTransicion *)malloc(sizeof(NodoTransicion));
    if (!nuevo) {
        printf("Error de memoria al crear nodo de transición.\n");
        exit(1);
    }
    nuevo->destino = destino;
    nuevo->siguiente = NULL;
    return nuevo;
}

// Función para crear un AFN vacío
AFN *crearAFN(int numEstados, int numSimbolos) {
    AFN *afn = (AFN *)malloc(sizeof(AFN));
    if (!afn) {
        printf("Error de memoria al crear AFN.\n");
        exit(1);
    }

    // Inicializar estructura
    afn->numEstados = numEstados;
    afn->numSimbolos = numSimbolos;
    afn->tieneEpsilon = 1;                 // Siempre incluimos epsilon
    afn->indiceEpsilon = numSimbolos - 1;  // El último símbolo siempre será epsilon

    // Inicializar arreglos
    afn->estados = (char **)malloc(numEstados * sizeof(char *));
    afn->alfabeto = (char **)malloc(numSimbolos * sizeof(char *));
    afn->finales = (int *)calloc(numEstados, sizeof(int));

    if (!afn->estados || !afn->alfabeto || !afn->finales) {
        printf("Error de memoria al crear AFN.\n");
        liberarAFN(afn);
        exit(1);
    }

    // Inicializar matriz de transiciones
    afn->transiciones = (NodoTransicion ***)malloc(numEstados * sizeof(NodoTransicion **));
    if (!afn->transiciones) {
        printf("Error de memoria al crear AFN.\n");
        liberarAFN(afn);
        exit(1);
    }

    for (int i = 0; i < numEstados; i++) {
        afn->transiciones[i] = (NodoTransicion **)malloc(numSimbolos * sizeof(NodoTransicion *));
        if (!afn->transiciones[i]) {
            printf("Error de memoria al crear AFN.\n");
            liberarAFN(afn);
            exit(1);
        }

        for (int j = 0; j < numSimbolos; j++) {
            afn->transiciones[i][j] = NULL;
        }
    }

    return afn;
}

AFN *cargarAFN(const char *nombreArchivo) {
    FILE *f = fopen(nombreArchivo, "r");
    if (!f) {
        printf("Error al abrir el archivo %s\n", nombreArchivo);
        return NULL;
    }
    char linea[256];
    int contador;

    // --- Primera línea: Nombres de estados ---
    if (!fgets(linea, sizeof(linea), f)) {
        fclose(f);
        return NULL;
    }
    int len = longitud_cadena(linea);
    if (len > 0 && linea[len - 1] == '\n')
        linea[len - 1] = '\0';
    char **tokensEstados = dividir_cadena(linea, ',', &contador);
    int numEstados = contador;

    // --- Segunda línea: Alfabeto ---
    if (!fgets(linea, sizeof(linea), f)) {
        for (int i = 0; i < numEstados; i++)
            free(tokensEstados[i]);
        free(tokensEstados);
        fclose(f);
        return NULL;
    }
    len = longitud_cadena(linea);
    if (len > 0 && linea[len - 1] == '\n')
        linea[len - 1] = '\0';
    char **tokensAlfabeto = dividir_cadena(linea, ',', &contador);

    // Verificar si epsilon ya está en el alfabeto
    int tieneEpsilonExplicito = 0;
    for (int i = 0; i < contador && !tieneEpsilonExplicito; i++) {
        char *temp = trim_cadena(tokensAlfabeto[i]);
        tieneEpsilonExplicito = (strcmp(temp, EPSILON_SYMBOL) == 0);
        free(temp);
    }

    // Añadir epsilon al alfabeto si no está presente
    int numSimbolos;
    char **alfabetoFinal;

    if (!tieneEpsilonExplicito) {
        numSimbolos = contador + 1;
        alfabetoFinal = (char **)malloc(numSimbolos * sizeof(char *));

        // Copiar símbolos originales
        for (int i = 0; i < contador; i++) {
            alfabetoFinal[i] = copia_cadena(tokensAlfabeto[i]);
        }

        // Añadir epsilon como último símbolo
        alfabetoFinal[contador] = copia_cadena(EPSILON_SYMBOL);
    } else {
        // Usar el alfabeto tal como está
        numSimbolos = contador;
        alfabetoFinal = (char **)malloc(numSimbolos * sizeof(char *));

        for (int i = 0; i < contador; i++) {
            alfabetoFinal[i] = copia_cadena(tokensAlfabeto[i]);
        }
    }

    // Liberar tokens originales
    for (int i = 0; i < contador; i++) {
        free(tokensAlfabeto[i]);
    }
    free(tokensAlfabeto);

    // Crear el AFN
    AFN *afn = crearAFN(numEstados, numSimbolos);
    if (!afn) {
        for (int i = 0; i < numEstados; i++)
            free(tokensEstados[i]);
        free(tokensEstados);
        for (int i = 0; i < numSimbolos; i++)
            free(alfabetoFinal[i]);
        free(alfabetoFinal);
        fclose(f);
        return NULL;
    }

    // Guardar nombres de estados
    for (int i = 0; i < numEstados; i++) {
        char *temp = trim_cadena(tokensEstados[i]);
        afn->estados[i] = copia_cadena(temp);
        free(temp);
        free(tokensEstados[i]);
    }
    free(tokensEstados);

    // Guardar alfabeto y encontrar el índice de epsilon
    afn->tieneEpsilon = 1;  // Siempre tendrá epsilon
    afn->indiceEpsilon = -1;

    for (int i = 0; i < numSimbolos; i++) {
        afn->alfabeto[i] = alfabetoFinal[i];
        // Verificar si es epsilon
        if (strcmp(alfabetoFinal[i], EPSILON_SYMBOL) == 0) {
            afn->indiceEpsilon = i;
        }
    }
    free(alfabetoFinal);

    // Verificar que se encontró el índice de epsilon
    if (afn->indiceEpsilon == -1) {
        printf("Error: No se pudo determinar el índice de epsilon.\n");
        liberarAFN(afn);
        fclose(f);
        return NULL;
    }

    // --- Tercera línea: Estado Inicial (nombre) ---
    if (!fgets(linea, sizeof(linea), f)) {
        fclose(f);
        liberarAFN(afn);
        return NULL;
    }
    len = longitud_cadena(linea);
    if (len > 0 && linea[len - 1] == '\n')
        linea[len - 1] = '\0';
    int ini = indiceEstado(afn, linea);
    if (ini == -1) {
        printf("Estado inicial '%s' no encontrado.\n", linea);
        fclose(f);
        liberarAFN(afn);
        return NULL;
    }
    afn->estadoInicial = ini;

    // --- Cuarta línea: Estados Finales (nombres) ---
    if (!fgets(linea, sizeof(linea), f)) {
        fclose(f);
        liberarAFN(afn);
        return NULL;
    }
    len = longitud_cadena(linea);
    if (len > 0 && linea[len - 1] == '\n')
        linea[len - 1] = '\0';
    char **tokensFinales = dividir_cadena(linea, ',', &contador);
    for (int i = 0; i < contador; i++) {
        int indice = indiceEstado(afn, tokensFinales[i]);
        if (indice != -1)
            afn->finales[indice] = 1;
        else
            printf("Estado final '%s' no encontrado.\n", tokensFinales[i]);
        free(tokensFinales[i]);
    }
    free(tokensFinales);

    // --- Resto: Transiciones ---
    while (fgets(linea, sizeof(linea), f)) {
        len = longitud_cadena(linea);
        if (len > 0 && linea[len - 1] == '\n')
            linea[len - 1] = '\0';
        if (len == 0)
            continue;
        int cont;
        char **tokens = dividir_cadena(linea, ',', &cont);
        if (cont < 3) {
            for (int i = 0; i < cont; i++)
                free(tokens[i]);
            free(tokens);
            continue;
        }
        char *origen = tokens[0];
        char *simbolo = tokens[1];
        char *destino = tokens[2];
        agregarTransicion(afn, origen, simbolo, destino);
        for (int i = 0; i < cont; i++)
            free(tokens[i]);
        free(tokens);
    }
    fclose(f);
    return afn;
}

void liberarAFN(AFN *afn) {
    if (!afn)
        return;
    // Liberar nombres de estados
    for (int i = 0; i < afn->numEstados; i++) {
        free(afn->estados[i]);
    }
    free(afn->estados);

    // Liberar alfabeto
    for (int i = 0; i < afn->numSimbolos; i++) {
        free(afn->alfabeto[i]);
    }
    free(afn->alfabeto);

    // Liberar estados finales
    free(afn->finales);

    // Liberar matriz de transiciones
    for (int i = 0; i < afn->numEstados; i++) {
        for (int j = 0; j < afn->numSimbolos; j++) {
            NodoTransicion *nodo = afn->transiciones[i][j];
            while (nodo) {
                NodoTransicion *temp = nodo;
                nodo = nodo->siguiente;
                free(temp);
            }
        }
        free(afn->transiciones[i]);
    }
    free(afn->transiciones);

    // Liberar el AFN
    free(afn);
}

void imprimirAFN(AFN *afn) {
    if (!afn) {
        printf("AFN no inicializado.\n");
        return;
    }

    printf("Estado inicial: %s\n", afn->estados[afn->estadoInicial]);

    printf("Estados: ");
    for (int i = 0; i < afn->numEstados; i++) {
        printf("%s", afn->estados[i]);
        if (i < afn->numEstados - 1)
            printf(", ");
    }
    printf("\n");

    printf("Estados finales: ");
    int primero = 1;
    for (int i = 0; i < afn->numEstados; i++) {
        if (afn->finales[i]) {
            if (!primero)
                printf(", ");
            printf("%s", afn->estados[i]);
            primero = 0;
        }
    }
    printf("\n");

    printf("Alfabeto: ");
    for (int i = 0; i < afn->numSimbolos; i++) {
        printf("%s", afn->alfabeto[i]);
        if (i < afn->numSimbolos - 1)
            printf(", ");
    }
    printf("\n");

    printf("Transiciones:\n");
    for (int i = 0; i < afn->numEstados; i++) {
        for (int j = 0; j < afn->numSimbolos; j++) {
            NodoTransicion *trans = afn->transiciones[i][j];
            while (trans) {
                printf("%s, %s -> %s\n",
                       afn->estados[i],
                       afn->alfabeto[j],
                       afn->estados[trans->destino]);
                trans = trans->siguiente;
            }
        }
    }
}

void agregarTransicion(AFN *afn, char *origen, char *simbolo, char *destino) {
    int indOrigen = indiceEstado(afn, origen);
    int indSimbolo = indiceSimbolo(afn, simbolo);
    int indDestino = indiceEstado(afn, destino);

    if (indOrigen == -1 || indSimbolo == -1 || indDestino == -1) {
        printf("Error: Estado u símbolo no encontrado en la transición (%s,%s,%s)\n",
               origen, simbolo, destino);
        return;
    }

    NodoTransicion *nuevo = crearNodoTransicion(indDestino);
    nuevo->siguiente = afn->transiciones[indOrigen][indSimbolo];
    afn->transiciones[indOrigen][indSimbolo] = nuevo;
}

int indiceSimbolo(AFN *afn, char *simbolo) {
    for (int i = 0; i < afn->numSimbolos; i++) {
        if (strcmp(afn->alfabeto[i], simbolo) == 0)
            return i;
    }
    return -1;
}

int indiceEstado(AFN *afn, char *estado) {
    for (int i = 0; i < afn->numEstados; i++) {
        if (strcmp(afn->estados[i], estado) == 0)
            return i;
    }
    return -1;
}

int esEpsilon(AFN *afn, int indiceSimbolo) {
    return afn->tieneEpsilon && indiceSimbolo == afn->indiceEpsilon;
}

// Funciones para manejar conjuntos de estados

ConjuntoEstados *crearConjuntoEstados(int capacidadInicial) {
    ConjuntoEstados *conjunto = (ConjuntoEstados *)malloc(sizeof(ConjuntoEstados));
    if (!conjunto) {
        printf("Error de memoria al crear conjunto de estados.\n");
        exit(1);
    }

    conjunto->estados = (int *)malloc(capacidadInicial * sizeof(int));
    if (!conjunto->estados) {
        printf("Error de memoria al crear arreglo de estados.\n");
        free(conjunto);
        exit(1);
    }

    conjunto->numEstados = 0;
    conjunto->capacidad = capacidadInicial;

    return conjunto;
}

void liberarConjuntoEstados(ConjuntoEstados *conjunto) {
    if (!conjunto)
        return;
    free(conjunto->estados);
    free(conjunto);
}

void agregarEstado(ConjuntoEstados *conjunto, int estado) {
    // Verificar si el estado ya está en el conjunto
    for (int i = 0; i < conjunto->numEstados; i++) {
        if (conjunto->estados[i] == estado)
            return;  // Ya existe, no agregar duplicados
    }

    // Verificar si se necesita ampliar el arreglo
    if (conjunto->numEstados >= conjunto->capacidad) {
        int nuevaCapacidad = conjunto->capacidad * 2;
        int *nuevosEstados = (int *)realloc(conjunto->estados, nuevaCapacidad * sizeof(int));
        if (!nuevosEstados) {
            printf("Error de memoria al redimensionar conjunto de estados.\n");
            exit(1);
        }
        conjunto->estados = nuevosEstados;
        conjunto->capacidad = nuevaCapacidad;
    }

    // Agregar el estado al conjunto
    conjunto->estados[conjunto->numEstados++] = estado;
}

int contieneEstado(ConjuntoEstados *conjunto, int estado) {
    for (int i = 0; i < conjunto->numEstados; i++) {
        if (conjunto->estados[i] == estado)
            return 1;
    }
    return 0;
}

// Calcular la clausura epsilon para un estado
ConjuntoEstados *clausuraEpsilon(AFN *afn, int estado) {
    // Si no hay epsilon, la clausura es solo el estado mismo
    if (!afn->tieneEpsilon) {
        ConjuntoEstados *resultado = crearConjuntoEstados(1);
        agregarEstado(resultado, estado);
        return resultado;
    }

    // Crear conjunto para la clausura
    ConjuntoEstados *clausura = crearConjuntoEstados(afn->numEstados);

    // Usamos un arreglo para simular una pila para el recorrido DFS
    int *pila = (int *)malloc(afn->numEstados * sizeof(int));
    int tope = 0;

    // Inicializar con el estado actual
    pila[tope++] = estado;
    agregarEstado(clausura, estado);

    // Proceso de DFS
    while (tope > 0) {
        int estadoActual = pila[--tope];

        // Obtener todas las transiciones epsilon desde este estado
        NodoTransicion *trans = afn->transiciones[estadoActual][afn->indiceEpsilon];

        while (trans) {
            int estadoDestino = trans->destino;

            // Si este estado no está en la clausura, agregarlo y procesarlo
            if (!contieneEstado(clausura, estadoDestino)) {
                agregarEstado(clausura, estadoDestino);
                pila[tope++] = estadoDestino;
            }

            trans = trans->siguiente;
        }
    }

    free(pila);
    return clausura;
}

// Calcular la clausura epsilon para un conjunto de estados
ConjuntoEstados *clausuraEpsilonConjunto(AFN *afn, ConjuntoEstados *conjunto) {
    // Si no hay epsilon, la clausura es el mismo conjunto
    if (!afn->tieneEpsilon) {
        // Crear una copia del conjunto
        ConjuntoEstados *resultado = crearConjuntoEstados(conjunto->numEstados);
        for (int i = 0; i < conjunto->numEstados; i++) {
            agregarEstado(resultado, conjunto->estados[i]);
        }
        return resultado;
    }

    // Crear conjunto para la clausura
    ConjuntoEstados *clausura = crearConjuntoEstados(afn->numEstados);

    // Para cada estado en el conjunto, calcular su clausura y agregar al resultado
    for (int i = 0; i < conjunto->numEstados; i++) {
        ConjuntoEstados *clausuraDelEstado = clausuraEpsilon(afn, conjunto->estados[i]);

        // Agregar todos los estados de la clausura al resultado
        for (int j = 0; j < clausuraDelEstado->numEstados; j++) {
            agregarEstado(clausura, clausuraDelEstado->estados[j]);
        }

        liberarConjuntoEstados(clausuraDelEstado);
    }

    return clausura;
}

// DFS modificado para soportar transiciones epsilon
void dfs(AFN *afn, int estadoActual, const char *cadena, int pos, int longitud,
         int *camino, char *caminoSimbolos, int indiceCamino, NodoRecorrido **listaRecorridos) {
    // Guardar el estado actual en el camino
    camino[indiceCamino] = estadoActual;

    // Caso 1: Hemos llegado al final de la cadena
    if (pos == longitud) {
        // Verificar si el estado actual es de aceptación
        if (afn->finales[estadoActual]) {
            guardarRecorrido(afn, camino, caminoSimbolos, indiceCamino + 1, listaRecorridos);
        }

        // Explorar transiciones epsilon desde este estado final
        if (afn->tieneEpsilon) {
            explorarTransicionesEpsilon(afn, estadoActual, cadena, pos, longitud,
                                        camino, caminoSimbolos, indiceCamino, listaRecorridos);
        }

        return;
    }

    // Caso 2: Explorar transiciones epsilon antes de consumir símbolo
    if (afn->tieneEpsilon) {
        explorarTransicionesEpsilon(afn, estadoActual, cadena, pos, longitud,
                                    camino, caminoSimbolos, indiceCamino, listaRecorridos);
    }

    // Caso 3: Consumir el símbolo actual de la cadena
    char simboloActual[2] = {cadena[pos], '\0'};
    int indSimbolo = indiceSimbolo(afn, simboloActual);

    if (indSimbolo != -1) {
        // Guardar el símbolo consumido
        caminoSimbolos[indiceCamino] = cadena[pos];

        // Explorar todas las transiciones con este símbolo
        NodoTransicion *trans = afn->transiciones[estadoActual][indSimbolo];
        while (trans) {
            dfs(afn, trans->destino, cadena, pos + 1, longitud,
                camino, caminoSimbolos, indiceCamino + 1, listaRecorridos);
            trans = trans->siguiente;
        }
    }
}

// Función auxiliar para explorar transiciones epsilon
void explorarTransicionesEpsilon(AFN *afn, int estadoActual, const char *cadena, int pos, int longitud,
                                 int *camino, char *caminoSimbolos, int indiceCamino,
                                 NodoRecorrido **listaRecorridos) {
    NodoTransicion *trans = afn->transiciones[estadoActual][afn->indiceEpsilon];
    while (trans) {
        // Para las transiciones epsilon, usamos 'e' como símbolo
        caminoSimbolos[indiceCamino] = 'e';
        dfs(afn, trans->destino, cadena, pos, longitud,
            camino, caminoSimbolos, indiceCamino + 1, listaRecorridos);
        trans = trans->siguiente;
    }
}

// Función auxiliar para guardar un recorrido de aceptación
void guardarRecorrido(AFN *afn, int *camino, char *simbolos, int longitud,
                      NodoRecorrido **listaRecorridos) {
    // Crear un nuevo nodo de recorrido para guardar este camino
    NodoRecorrido *nuevo = (NodoRecorrido *)malloc(sizeof(NodoRecorrido));
    if (!nuevo) {
        printf("Error de memoria al crear nodo de recorrido.\n");
        exit(1);
    }

    nuevo->longitud = longitud;
    nuevo->estados = (int *)malloc(longitud * sizeof(int));
    nuevo->simbolos = (char *)malloc(longitud * sizeof(char));

    if (!nuevo->estados || !nuevo->simbolos) {
        printf("Error de memoria al crear arrays de recorrido.\n");
        free(nuevo->estados);
        free(nuevo->simbolos);
        free(nuevo);
        exit(1);
    }

    // Copiar el camino y los símbolos
    for (int i = 0; i < longitud; i++) {
        nuevo->estados[i] = camino[i];
    }

    for (int i = 0; i < longitud - 1; i++) {
        nuevo->simbolos[i] = simbolos[i];
    }
    nuevo->simbolos[longitud - 1] = '\0';

    // Insertar al inicio de la lista
    nuevo->siguiente = *listaRecorridos;
    *listaRecorridos = nuevo;
}

// Imprime un recorrido usando los nombres de estado y los símbolos consumidos
void imprimirRecorridoConNombres(AFN *afn, int *camino, char *simbolos, int longitud) {
    // Para cada estado en el recorrido
    for (int i = 0; i < longitud; i++) {
        // Imprime el nombre del estado entre llaves
        printf("{%s}", afn->estados[camino[i]]);

        // Si no es el último, muestra el símbolo consumido para llegar al siguiente
        if (i < longitud - 1) {
            // Mostrar epsilon como ε
            if (simbolos[i] == 'e') {
                printf("(ε) -> ");
            } else {
                printf("(%c) -> ", simbolos[i]);
            }
        }
    }
    printf("\n");
}

void imprimirRecorridosConNombres(AFN *afn, NodoRecorrido *lista) {
    if (!lista) {
        printf("No se encontraron recorridos de aceptación.\n");
        return;
    }

    printf("Listado de caminos:\n");
    int contador = 1;
    NodoRecorrido *actual = lista;

    while (actual) {
        printf("Camino %d: ", contador);
        imprimirRecorridoConNombres(afn, actual->estados, actual->simbolos, actual->longitud);
        actual = actual->siguiente;
        contador++;
    }
}
