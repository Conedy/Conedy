import conedy as co

n = co.network()

n.addNode (co.node())
n.addEdge (0,0,co.weightedEdge(1.0))
n.removeEdges(co.weightedEdge())
print "Should be 0:"
print n.meanDegree()
n.clear()


n.cycle( 10000, 2,  co.node(), co.staticWeightedEdge(1.0))


n.replaceEdges (0.5, co.weightedEdge())
print "Should be 4:"
print n.meanDegree()

n.removeEdges (co.weightedEdge())


print "Should be close to 2:"
print n.meanDegree()

