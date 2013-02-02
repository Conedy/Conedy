import conedy as co

net = co.network()




net.addNode (co.node())
net.addEdge (0,0,co.weightedEdge(1.0))
net.removeEdges(co.weightedEdge())
print "Should be 0:" + str(net.meanDegree())
net.clear()


net.cycle (10000, 2, co.node(), co.staticWeightedEdge())


net.rewire (0.5, co.weightedEdge(1.0))
print "Should be 4:" + str(net.meanDegree())

net.removeEdges (co.weightedEdge(1.0))


print "Should be close to 2:" + str(net.meanDegree())

