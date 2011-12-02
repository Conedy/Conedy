import conedy as co


net = co.network()

for i in range (0,100):
	net.addNode(co.node())

net.addRandomEdges (10.0, co.weightedEdge(0.5))



print "should be 10:" + str(net.meanDegree())
