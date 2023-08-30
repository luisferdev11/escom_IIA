// Función para unir nodos en el grafo que cumplan la condición ((x + y) % n) == m
function unirNodos(graph, n, m) {
  const nodes = Object.keys(graph);

  for (let i = 0; i < nodes.length; i++) {
    const x = nodes[i];

    for (let j = 0; j < nodes.length; j++) {
      const y = nodes[j];

      if ((parseInt(x) + parseInt(y)) % n === m) {
        graph[x].push(y);
      }
    }
  }

  return graph;
}

// Función para generar el grafo basado en los valores de n y m ingresados por el usuario
function generarGrafo() {
  const nInput = document.getElementById("n-input");
  const mInput = document.getElementById("m-input");
  const n = parseInt(nInput.value);
  const m = parseInt(mInput.value);

  // Generar los nodos basados en el valor de n
  const nodes = {};
  for (let i = 0; i < n; i++) {
    nodes[i] = [];
  }

  // Unir los nodos que cumplen la condición en el grafo
  const grafoResultante = unirNodos(nodes, n, m);

  // Crear los nodos y las aristas para vis.js
  const visNodes = new vis.DataSet(
    Object.keys(grafoResultante).map((node) => ({ id: node, label: `${node}` }))
  );
  const visEdges = new vis.DataSet();

  // Agregar las aristas al grafo con flechas en ambos lados
  Object.keys(grafoResultante).forEach((node) => {
    const neighbors = grafoResultante[node];
    neighbors.forEach((neighbor) => {
      visEdges.add([
        {
          from: node,
          to: neighbor,
          arrows: { to: { enabled: true, scaleFactor: 0.8 } },
        },
        {
          from: neighbor,
          to: node,
          arrows: { to: { enabled: true, scaleFactor: 0.8 } },
        },
      ]);
    });
  });

  // Configurar el diseño en forma de círculo
  const options = {
    layout: {
      hierarchical: {
        sortMethod: "directed",
        direction: "LR",
      },
    },
  };

  const container = document.getElementById("graph-container");
  const data = { nodes: visNodes, edges: visEdges };

  // Crear la red y visualizar el grafo
  const network = new vis.Network(container, data, options);
}
