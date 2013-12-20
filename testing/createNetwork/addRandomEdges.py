import conedy as co


N = co.network()

for i in range (0,100):
	N.addNode(co.node())

N.addRandomEdges (10.0, co.weightedEdge(0.5))



print "should be 10:" + str(N.meanDegree())
