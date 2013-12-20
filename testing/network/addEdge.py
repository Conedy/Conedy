import conedy as co

N = co.network()

N.addNode(co.node())
N.addNode()

N.addEdge(0,1,co.weightedEdge(0.3))
N.addEdge(1,0,staticWeightedEdge(0.3));


N.saveAdjacencyList("output/addEdge.py.adjList")
