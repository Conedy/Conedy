import conedy as co


N = co.undirectedNetwork()

for i in range (0,100):
	N.addNode(co.node())

N.addRandomEdges (10.0, co.weightedEdge(0.5))

print "should be 10:" + str(N.meanDegree())
print "should be true:" + str(N.isDirected())

N.setDirected();

N.addRandomEdges (20.0, co.weightedEdge (0.5))

print "should be 20:" + str(N.meanDegree())
print "should be false:" + str(N.isDirected())


