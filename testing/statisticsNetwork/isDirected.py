import conedy as co

net = co.network()

net.addNode(co.kuramoto())
net.addNode(co.kuramoto())

net.addEdge (0,1, co.weightedEdge(2.0))
print "Should be true: " + str (net.isDirected())
net.addEdge (1,0, co.weightedEdge(0.1))
print "Should be true: " + str (net.isDirected())
net.randomizeWeights(co.uniform (3.0,3.0))
print "Should be false: " + str (net.isDirected())


