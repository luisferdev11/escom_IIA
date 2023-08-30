import networkx as nx
import matplotlib.pyplot as plt


def draw_graph(graph):
    pos = nx.spring_layout(graph)
    nx.draw_networkx_nodes(graph, pos)
    nx.draw_networkx_labels(graph, pos)
    nx.draw_networkx_edges(graph, pos)
    plt.show()


def adjacency_matrix(graph):
    nodes = list(graph.nodes)
    matrix = [[0]*len(nodes) for _ in range(len(nodes))]

    for edge in graph.edges:
        matrix[edge[0]][edge[1]] = 1
        matrix[edge[1]][edge[0]] = 1
    return matrix


def incidence_matrix(graph):
    nodes = list(graph.nodes)
    edges = list(graph.edges)
    matrix = [[0]*len(edges) for _ in range(len(nodes))]

    for idx, edge in enumerate(edges):
        matrix[edge[0]][idx] = 1
        matrix[edge[1]][idx] = 1
    return matrix


def most_connected_vertex(graph):
    return max(graph, key=graph.degree)


vertices = int(input("Ingrese la cantidad de vértices: "))
edges = int(input("Ingrese la cantidad de aristas: "))

G = nx.Graph()

for i in range(vertices):
    G.add_node(i)

for _ in range(edges):
    u, v = map(int, input(
        "Ingrese los vértices relacionados por una arista (separados por un espacio): ").split())
    G.add_edge(u, v)

print("Matriz de adyacencia:")
for row in adjacency_matrix(G):
    print(row)

print("Matriz de incidencia:")
for row in incidence_matrix(G):
    print(row)

print(f"El vértice más conectado es: {most_connected_vertex(G)}")

draw_graph(G)
