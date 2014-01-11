import conedy as co

n = co.network()

n.addNode (node())
n.addEdge (0,0,co.weightedEdge(1.0))
n.removeEdges(co.weightedEdge)
print "Should be 0:"
print n.meanDegree()
print newline
n.clear()


n.cycle( 10000, 2,  node(), staticWeightedEdge(1.0))


n.rewire (0.5, co.weightedEdge)
print "Should be 4:"
print n.meanDegree()
print newline

n.removeEdges (co.weightedEdge)


print "Should be close to 2:"
print n.meanDegree()
print newline

