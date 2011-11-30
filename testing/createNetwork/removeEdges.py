import conedy as co

net = co.network()




net.addNode (co.node())
net.addEdge (0,0,co.weightedEdge(1.0))
net.removeEdges(co.weightedEdge())
print "Should be 0:"
print net.meanDegree()
print newline
net.clear()


net.cycle (10000, 2, co.node(), co.staticWeightedEdge())


net.rewire (0.5, co.weightedEdge())
print "Should be 4:" + str(net.meanDegree())

net.removeEdges (co.weightedEdge())


print "Should be close to 2:" + str(net.meanDegree())

