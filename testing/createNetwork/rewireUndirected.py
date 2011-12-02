import conedy as co

net = co.network()



net.cycle( 100, 10,co.node(), co.staticWeightedEdge())

#net.printNodeStatistics();

print "should be 20:"+ str(net.meanDegree())
net.rewireUndirected(1.0)
print "should be 20:"+ str(net.meanDegree())
net.saveAdjacencyList("output/rewireUndirected.py.graph")

if (net.isDirected()):
	print "Error: The network is directed."




