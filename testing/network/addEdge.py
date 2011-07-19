import conedy as co

net = co.network()

net.addNode(co.node())
net.addNode(co.node())

#net.addEdge(0,1,co.weightedEdge(0.3))

net.addEdge(0,1,co.weightedEdge(0.3))


net.saveAdjacencyList("output/addEdge.py.adjList")
