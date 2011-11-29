import conedy as co

net = co.network()




net.addNode <node>()
net.addEdge (0,0,1.0,weightedEdge())
net.removeEdges(weightedEdge())
print "Should be 0:"
print net.meanDegree()
print newline
net.clear()


net.cycle (10000, 2, node, staticWeightedEdge())


net.rewire (0.5, weightedEdge())
print "Should be 4:"
print net.meanDegree()
print newline

net.removeEdges (weightedEdge())


print "Should be close to 2:"
print net.meanDegree()
print newline

