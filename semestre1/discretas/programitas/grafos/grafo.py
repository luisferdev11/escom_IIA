import networkx as nx
import matplotlib.pyplot as plt


def unir_nodos(graph, n, m):
    nodes = list(graph.nodes)
    [graph.add_edge(x, y) for x in nodes for y in nodes if (int(x) + int(y)) % n == m]
    return graph


def generar_grafo(n, m):
    grafo = nx.DiGraph()
    [grafo.add_node(str(i)) for i in range(n)]
    # Cambiamos los colores a un tono guinda

    grafo_resultante = unir_nodos(grafo, n, m)

    if n == 2 and m == 0:
        nx.draw_random(
            grafo_resultante,
            with_labels=True,
            node_color="#ce8def",
            node_size=500,
            font_size=10,
            edge_color="#800000",
        )
    else:
        nx.draw_circular(
            grafo_resultante,
            with_labels=True,
            node_color="#ce8def",
            node_size=200,
            font_size=10,
            edge_color="#800000",
        )
    plt.show()


n = int(input("Ingrese el valor de n: "))
m = int(input("Ingrese el valor de m: "))

generar_grafo(n, m)
