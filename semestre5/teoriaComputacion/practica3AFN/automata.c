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
        fclose(f);
        return NULL;
    }
    len = longitud_cadena(linea);
    if (len > 0 && linea[len - 1] == '\n')
        linea[len - 1] = '\0';
    char **tokensAlfabeto = dividir_cadena(linea, ',', &contador);
    int numSimbolos = contador;

    // Crear el AFN
    AFN *afn = (AFN *)malloc(sizeof(AFN));
    if (!afn) {
        printf("Error de memoria al crear AFN.\n");
        exit(1);
    }
    afn->numEstados = numEstados;
    afn->numSimbolos = numSimbolos;

    // Guardar nombres de estados
    afn->estados = (char **)malloc(numEstados * sizeof(char *));
    for (int i = 0; i < numEstados; i++) {
        char *temp = trim_cadena(tokensEstados[i]);
        afn->estados[i] = copia_cadena(temp);
        free(temp);
        free(tokensEstados[i]);
    }
    free(tokensEstados);

    // Guardar alfabeto
    afn->alfabeto = (char **)malloc(numSimbolos * sizeof(char *));
    for (int i = 0; i < numSimbolos; i++) {
        afn->alfabeto[i] = copia_cadena(tokensAlfabeto[i]);
        free(tokensAlfabeto[i]);
    }
    free(tokensAlfabeto);

    // --- Tercera línea: Estado Inicial (nombre) ---
    if (!fgets(linea, sizeof(linea), f)) {
        fclose(f);
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
        return NULL;
    }
    len = longitud_cadena(linea);
    if (len > 0 && linea[len - 1] == '\n')
        linea[len - 1] = '\0';
    char **tokensFinales = dividir_cadena(linea, ',', &contador);
    afn->finales = (int *)calloc(numEstados, sizeof(int));
    for (int i = 0; i < contador; i++) {
        int indice = indiceEstado(afn, tokensFinales[i]);
        if (indice != -1)
            afn->finales[indice] = 1;
        else
            printf("Estado final '%s' no encontrado.\n", tokensFinales[i]);
        free(tokensFinales[i]);
    }
    free(tokensFinales);

    // Inicializar matriz de transiciones
    afn->transiciones = (NodoTransicion ***)malloc(numEstados * sizeof(NodoTransicion **));
    for (int i = 0; i < numEstados; i++) {
        afn->transiciones[i] = (NodoTransicion **)malloc(numSimbolos * sizeof(NodoTransicion *));
        for (int j = 0; j < numSimbolos; j++) {
            afn->transiciones[i][j] = NULL;
        }
    }

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
    for (int i = 0; i < afn->numEstados; i++) {
        free(afn->estados[i]);
    }
    free(afn->estados);
    for (int i = 0; i < afn->numSimbolos; i++) {
        free(afn->alfabeto[i]);
    }
    free(afn->alfabeto);
    free(afn->finales);
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
    free(afn);
}

void agregarTransicion(AFN *afn, char *origen, char *simbolo, char *destino) {
    int indOrigen = indiceEstado(afn, origen);
    int indSimbolo = indiceSimbolo(afn, simbolo);
    int indDestino = indiceEstado(afn, destino);
    if (indOrigen == -1 || indSimbolo == -1 || indDestino == -1) {
        return;
    }
    NodoTransicion *nuevo = crearNodoTransicion(indDestino);
    nuevo->siguiente = afn->transiciones[indOrigen][indSimbolo];
    afn->transiciones[indOrigen][indSimbolo] = nuevo;
}

int indiceSimbolo(AFN *afn, char *simbolo) {
    for (int i = 0; i < afn->numSimbolos; i++) {
        int j = 0;
        while (afn->alfabeto[i][j] != '\0' && simbolo[j] != '\0' &&
               afn->alfabeto[i][j] == simbolo[j])
            j++;
        if (afn->alfabeto[i][j] == '\0' && simbolo[j] == '\0')
            return i;
    }
    return -1;
}

int indiceEstado(AFN *afn, char *estado) {
    for (int i = 0; i < afn->numEstados; i++) {
        int j = 0;
        while (afn->estados[i][j] != '\0' && estado[j] != '\0' &&
               afn->estados[i][j] == estado[j])
            j++;
        if (afn->estados[i][j] == '\0' && estado[j] == '\0')
            return i;
    }
    return -1;
}

// DFS: además de almacenar el recorrido de estados, guarda los símbolos consumidos
void dfs(AFN *afn, int estadoActual, const char *cadena, int pos, int longitud,
         int *camino, char *caminoSimbolos, int indiceCamino, NodoRecorrido **listaRecorridos) {
    camino[indiceCamino] = estadoActual;
    indiceCamino++;

    if (pos == longitud) {
        if (afn->finales[estadoActual]) {
            NodoRecorrido *nuevo = (NodoRecorrido *)malloc(sizeof(NodoRecorrido));
            nuevo->longitud = indiceCamino;
            nuevo->estados = (int *)malloc(indiceCamino * sizeof(int));
            for (int i = 0; i < indiceCamino; i++)
                nuevo->estados[i] = camino[i];
            // Los símbolos consumidos son (indiceCamino - 1) caracteres
            nuevo->simbolos = (char *)malloc(indiceCamino * sizeof(char));
            for (int i = 0; i < indiceCamino - 1; i++)
                nuevo->simbolos[i] = caminoSimbolos[i];
            nuevo->simbolos[indiceCamino - 1] = '\0';
            nuevo->siguiente = *listaRecorridos;
            *listaRecorridos = nuevo;
        }
        return;
    } else {
        // Se consume el símbolo actual y se guarda
        char temp[2];
        temp[0] = cadena[pos];
        temp[1] = '\0';
        int indSimbolo = indiceSimbolo(afn, temp);
        if (indSimbolo != -1) {
            // Guardar el símbolo consumido en la posición correspondiente (para la transición que se toma)
            caminoSimbolos[indiceCamino - 1] = cadena[pos];
            NodoTransicion *trans = afn->transiciones[estadoActual][indSimbolo];
            while (trans) {
                dfs(afn, trans->destino, cadena, pos + 1, longitud,
                    camino, caminoSimbolos, indiceCamino, listaRecorridos);
                trans = trans->siguiente;
            }
        }
    }
}

// Imprime un recorrido usando los nombres de estado y los símbolos consumidos
void imprimirRecorridoConNombres(AFN *afn, int *camino, char *simbolos, int longitud) {
    // Para cada estado en el recorrido
    for (int i = 0; i < longitud; i++) {
        // Imprime el nombre del estado entre llaves
        printf("{%s", afn->estados[camino[i]]);
        // Si no es el último, muestra el símbolo consumido para llegar al siguiente
        if (i < longitud - 1) {
            printf("(%c)} -> ", simbolos[i]);
        } else {
            printf("}");
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
        printf("camino%d: ", contador);
        imprimirRecorridoConNombres(afn, actual->estados, actual->simbolos, actual->longitud);
        actual = actual->siguiente;
        contador++;
    }
}
