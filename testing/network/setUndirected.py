import conedy as co

N = co.undirectedNetwork()

N.addNode(co.node())
N.addNode(co.node())


N.addEdge(0,1,co.weightedEdge(1))


print "Should be false:" + str(N.isDirected())

N.removeEdges(co.weightedEdge(1))

N.setDirected()

N.addEdge(0,1,co.weightedEdge(1))

print "Should be true:" + str(N.isDirected())
