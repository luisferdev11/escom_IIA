#include <stdio.h>
#include <stdlib.h>

/* =================== Estructuras y Definiciones =================== */

// Nodo para la lista de transiciones
typedef struct TransitionNode {
    int dest;
    struct TransitionNode *next;
} TransitionNode;

// Estructura para almacenar un camino aceptado
typedef struct PathNode {
    int *states;            // Arreglo con la secuencia de estados
    int length;             // Longitud del camino (número de estados)
    struct PathNode *next;  // Siguiente camino en la lista
} PathNode;

// Representación interna del AFN
typedef struct {
    int numStates;     // Número total de estados
    int numSymbols;    // Número de símbolos en el alfabeto (sin contar epsilon)
    char **alphabet;   // Arreglo de cadenas para el alfabeto (cada símbolo es una cadena)
    int initialState;  // Estado inicial
    int *isFinal;      // Arreglo que indica (0 o 1) si un estado es final
    // Matriz de transiciones: para cada estado y cada símbolo, una lista enlazada de estados destino
    TransitionNode ***transitions;
    // Transiciones epsilon: para cada estado, lista enlazada de estados destino por epsilon
    TransitionNode **epsilonTransitions;
} NFA;

/* =================== Prototipos de Funciones =================== */

// Funciones de manejo de cadenas (sin usar string.h)
int my_strlen(const char *s);
int my_strcmp(const char *s1, const char *s2);
char *my_strdup(const char *s);
char **split(const char *str, char delimiter, int *count);

// Funciones para el manejo del AFN
NFA *createNFA(int numStates, int numSymbols);
void freeNFA(NFA *nfa);
void addTransition(NFA *nfa, int from, char *symbol, int to);
int findSymbolIndex(NFA *nfa, char *symbol);
NFA *loadNFA(const char *filename);

// DFS modificado para almacenar todos los caminos aceptados
void dfs(NFA *nfa, int currentState, const char *input, int pos, int inputLength,
         int *path, int pathIndex, int **visited, PathNode **acceptedPaths);

// Función para imprimir un camino (secuencia de estados)
void printPath(int *path, int length);
// Función para imprimir todos los caminos almacenados
void printAcceptedPaths(PathNode *head);

/* =================== Funciones Utilitarias de Cadenas =================== */

int my_strlen(const char *s) {
    int i = 0;
    while (s[i] != '\0')
        i++;
    return i;
}

int my_strcmp(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] && s2[i]) {
        if (s1[i] != s2[i])
            return s1[i] - s2[i];
        i++;
    }
    return s1[i] - s2[i];
}

char *my_strdup(const char *s) {
    int len = my_strlen(s);
    char *dup = (char *)malloc(len + 1);
    if (!dup) return NULL;
    for (int i = 0; i < len; i++)
        dup[i] = s[i];
    dup[len] = '\0';
    return dup;
}

// Versión corregida de la función split: separa la cadena en tokens usando el delimitador
char **split(const char *str, char delimiter, int *count) {
    int tokens = 0, i = 0;
    // Contar tokens
    while (str[i] != '\0') {
        while (str[i] == delimiter && str[i] != '\0')
            i++;
        if (str[i] == '\0')
            break;
        tokens++;
        while (str[i] != delimiter && str[i] != '\0')
            i++;
    }

    char **result = (char **)malloc(tokens * sizeof(char *));
    int tokenIndex = 0;
    i = 0;
    while (str[i] != '\0') {
        while (str[i] == delimiter && str[i] != '\0')
            i++;
        if (str[i] == '\0')
            break;
        int start = i;
        while (str[i] != delimiter && str[i] != '\0')
            i++;
        int length = i - start;
        char *token = (char *)malloc(length + 1);
        for (int j = 0; j < length; j++)
            token[j] = str[start + j];
        token[length] = '\0';
        result[tokenIndex++] = token;
    }
    *count = tokens;
    return result;
}

/* =================== Funciones para el Manejo del AFN =================== */

// Crea e inicializa la estructura NFA
NFA *createNFA(int numStates, int numSymbols) {
    NFA *nfa = (NFA *)malloc(sizeof(NFA));
    if (!nfa) return NULL;
    nfa->numStates = numStates;
    nfa->numSymbols = numSymbols;
    nfa->alphabet = (char **)malloc(numSymbols * sizeof(char *));
    nfa->isFinal = (int *)calloc(numStates, sizeof(int));
    // Inicializar matriz de transiciones
    nfa->transitions = (TransitionNode ***)malloc(numStates * sizeof(TransitionNode **));
    for (int i = 0; i < numStates; i++) {
        nfa->transitions[i] = (TransitionNode **)malloc(numSymbols * sizeof(TransitionNode *));
        for (int j = 0; j < numSymbols; j++)
            nfa->transitions[i][j] = NULL;
    }
    // Inicializar transiciones epsilon
    nfa->epsilonTransitions = (TransitionNode **)malloc(numStates * sizeof(TransitionNode *));
    for (int i = 0; i < numStates; i++)
        nfa->epsilonTransitions[i] = NULL;
    return nfa;
}

// Libera la memoria asignada al NFA
void freeNFA(NFA *nfa) {
    if (!nfa) return;
    for (int i = 0; i < nfa->numSymbols; i++)
        free(nfa->alphabet[i]);
    free(nfa->alphabet);
    free(nfa->isFinal);
    // Liberar transiciones (no epsilon)
    for (int i = 0; i < nfa->numStates; i++) {
        for (int j = 0; j < nfa->numSymbols; j++) {
            TransitionNode *node = nfa->transitions[i][j];
            while (node) {
                TransitionNode *tmp = node;
                node = node->next;
                free(tmp);
            }
        }
        free(nfa->transitions[i]);
    }
    free(nfa->transitions);
    // Liberar transiciones epsilon
    for (int i = 0; i < nfa->numStates; i++) {
        TransitionNode *node = nfa->epsilonTransitions[i];
        while (node) {
            TransitionNode *tmp = node;
            node = node->next;
            free(tmp);
        }
    }
    free(nfa->epsilonTransitions);
    free(nfa);
}

// Agrega una transición al NFA. Si 'symbol' es "epsilon" o "ε", se agrega a la lista de epsilon.
void addTransition(NFA *nfa, int from, char *symbol, int to) {
    if (!nfa) return;
    if (my_strcmp(symbol, "epsilon") == 0 || my_strcmp(symbol, "ε") == 0) {
        TransitionNode *newNode = (TransitionNode *)malloc(sizeof(TransitionNode));
        newNode->dest = to;
        newNode->next = nfa->epsilonTransitions[from];
        nfa->epsilonTransitions[from] = newNode;
    } else {
        int symIndex = findSymbolIndex(nfa, symbol);
        if (symIndex == -1)
            return;
        TransitionNode *newNode = (TransitionNode *)malloc(sizeof(TransitionNode));
        newNode->dest = to;
        newNode->next = nfa->transitions[from][symIndex];
        nfa->transitions[from][symIndex] = newNode;
    }
}

// Retorna el índice en el alfabeto para el símbolo dado; si no se encuentra, retorna -1.
int findSymbolIndex(NFA *nfa, char *symbol) {
    for (int i = 0; i < nfa->numSymbols; i++) {
        if (my_strcmp(nfa->alphabet[i], symbol) == 0)
            return i;
    }
    return -1;
}

// Carga el NFA desde un archivo con el formato especificado.
NFA *loadNFA(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Error al abrir el archivo %s\n", filename);
        return NULL;
    }
    char line[256];

    printf("Cargando archivo %s...\n", filename);

    // --- Primera línea: Estados ---
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        return NULL;
    }
    int len = my_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    int numStates = 0;
    char **statesTokens = split(line, ',', &numStates);

    // --- Segunda línea: Alfabeto ---
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        return NULL;
    }
    len = my_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    int numSymbols = 0;
    char **alphabetTokens = split(line, ',', &numSymbols);

    // Crear el NFA
    NFA *nfa = createNFA(numStates, numSymbols);
    for (int i = 0; i < numSymbols; i++) {
        nfa->alphabet[i] = my_strdup(alphabetTokens[i]);
        free(alphabetTokens[i]);
    }
    free(alphabetTokens);

    // --- Tercera línea: Estado Inicial ---
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        freeNFA(nfa);
        return NULL;
    }
    len = my_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    nfa->initialState = atoi(line);

    // --- Cuarta línea: Estados Finales ---
    if (!fgets(line, sizeof(line), f)) {
        fclose(f);
        freeNFA(nfa);
        return NULL;
    }
    len = my_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
        line[len - 1] = '\0';
    int numFinalTokens = 0;
    char **finalTokens = split(line, ',', &numFinalTokens);
    for (int i = 0; i < numFinalTokens; i++) {
        int state = atoi(finalTokens[i]);
        if (state >= 0 && state < numStates)
            nfa->isFinal[state] = 1;
        free(finalTokens[i]);
    }
    free(finalTokens);

    // --- Resto: Transiciones ---
    while (fgets(line, sizeof(line), f)) {
        len = my_strlen(line);
        if (len > 0 && line[len - 1] == '\n')
            line[len - 1] = '\0';
        if (len == 0)
            continue;
        int numTokens = 0;
        char **tokens = split(line, ',', &numTokens);
        if (numTokens < 3) {
            for (int i = 0; i < numTokens; i++)
                free(tokens[i]);
            free(tokens);
            continue;
        }
        int from = atoi(tokens[0]);
        char *symbol = tokens[1];
        int to = atoi(tokens[2]);
        addTransition(nfa, from, symbol, to);
        for (int i = 0; i < numTokens; i++)
            free(tokens[i]);
        free(tokens);
    }
    fclose(f);
    for (int i = 0; i < numStates; i++)
        free(statesTokens[i]);
    free(statesTokens);
    return nfa;
}

/* =================== DFS para Almacenar Todos los Caminos de Aceptación =================== */

void dfs(NFA *nfa, int currentState, const char *input, int pos, int inputLength,
         int *path, int pathIndex, int **visited, PathNode **acceptedPaths) {
    if (visited[currentState][pos])
        return;
    visited[currentState][pos] = 1;

    path[pathIndex] = currentState;
    pathIndex++;

    // Si se consumió toda la cadena y el estado es final, almacenar el camino
    if (pos == inputLength && nfa->isFinal[currentState]) {
        PathNode *newPath = (PathNode *)malloc(sizeof(PathNode));
        newPath->length = pathIndex;
        newPath->states = (int *)malloc(pathIndex * sizeof(int));
        for (int i = 0; i < pathIndex; i++) {
            newPath->states[i] = path[i];
        }
        newPath->next = *acceptedPaths;
        *acceptedPaths = newPath;
        // No se retorna; se continúa explorando posibles transiciones epsilon.
    }

    // Explorar transiciones epsilon (sin consumir símbolo)
    TransitionNode *ep = nfa->epsilonTransitions[currentState];
    while (ep) {
        dfs(nfa, ep->dest, input, pos, inputLength, path, pathIndex, visited, acceptedPaths);
        ep = ep->next;
    }

    // Si aún hay símbolos por consumir, explorar transiciones normales
    if (pos < inputLength) {
        char sym[2];
        sym[0] = input[pos];
        sym[1] = '\0';
        int symIndex = findSymbolIndex(nfa, sym);
        if (symIndex != -1) {
            TransitionNode *trans = nfa->transitions[currentState][symIndex];
            while (trans) {
                dfs(nfa, trans->dest, input, pos + 1, inputLength, path, pathIndex, visited, acceptedPaths);
                trans = trans->next;
            }
        }
    }
}

/* =================== Funciones para Imprimir Caminos =================== */

void printPath(int *path, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", path[i]);
        if (i < length - 1)
            printf(" -> ");
    }
    printf("\n");
}

void printAcceptedPaths(PathNode *head) {
    if (head == NULL) {
        printf("No se encontraron caminos de aceptación.\n");
        return;
    }
    printf("Caminos de aceptación:\n");
    PathNode *curr = head;
    while (curr) {
        printPath(curr->states, curr->length);
        curr = curr->next;
    }
}

/* =================== Función Principal =================== */

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <archivo_automata.txt>\n", argv[0]);
        return 1;
    }

    // Cargar el autómata desde el archivo
    NFA *nfa = loadNFA(argv[1]);
    if (nfa == NULL) {
        printf("Error al cargar el autómata.\n");
        return 1;
    }

    // Leer cadenas de entrada desde la entrada estándar
    char buffer[256];
    printf("Ingrese cadena (o 'salir' para terminar):\n");
    while (fgets(buffer, sizeof(buffer), stdin)) {
        int len = my_strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
            len--;
        }
        if (my_strcmp(buffer, "salir") == 0)
            break;

        // Preparar la matriz 'visited' para evitar ciclos: dimensiones [numStates][len+1]
        int **visited = (int **)malloc(nfa->numStates * sizeof(int *));
        for (int i = 0; i < nfa->numStates; i++)
            visited[i] = (int *)calloc(len + 1, sizeof(int));

        // Arreglo para almacenar el camino actual
        int *path = (int *)malloc((len + 1) * sizeof(int));
        // Lista de caminos aceptados (inicialmente vacía)
        PathNode *acceptedPaths = NULL;

        dfs(nfa, nfa->initialState, buffer, 0, len, path, 0, visited, &acceptedPaths);

        if (acceptedPaths)
            printAcceptedPaths(acceptedPaths);
        else
            printf("Cadena '%s' rechazada.\n", buffer);

        // Liberar la lista de caminos aceptados
        while (acceptedPaths) {
            PathNode *temp = acceptedPaths;
            acceptedPaths = acceptedPaths->next;
            free(temp->states);
            free(temp);
        }

        for (int i = 0; i < nfa->numStates; i++)
            free(visited[i]);
        free(visited);
        free(path);

        printf("Ingrese cadena (o 'salir' para terminar):\n");
    }

    freeNFA(nfa);
    return 0;
}
