import conedy as co

N = co.network()

N.addNode(co.node())
N.addNode(co.node())

#N.addEdge(0,1,co.weightedEdge(0.3))

N.addEdge(0,1,co.weightedEdge(0.3))


N.saveAdjacencyList("output/addEdge.py.adjList")
