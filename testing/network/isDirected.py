import conedy as co

N = co.network()

N.addNode(co.kuramoto())
N.addNode(co.kuramoto())

N.addEdge (0,1, co.weightedEdge(2.0))
print "Should be true: " + str (N.isDirected())
N.addEdge (1,0, co.weightedEdge(0.1))
print "Should be true: " + str (N.isDirected())
N.randomizeWeights(co.uniform (3.0, 3.0))
print "Should be false: " + str (N.isDirected())


