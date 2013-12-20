import conedy as co

N = co.undirectedNetwork()

N.addNode(node())
N.addNode(node())


N.addEdge(0,1,co.weightedEdge(1))


print "Should be false:" + N.isDirected()

N.removeEdges(co.weightedEdge(1))

N.setDirected()

N.addEdge(0,1,co.weightedEdge(1))

print "Should be true:" + N.isDirected()
