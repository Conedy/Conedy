import conedy as co

N = co.network()



N.cycle( 100, 10,co.node(), co.staticWeightedEdge())

#N.printNodeStatistics();

print "should be 20:"+ str(N.meanDegree())
N.rewireUndirected(1.0)
print "should be 20:"+ str(N.meanDegree())
N.saveAdjacencyList("output/rewireUndirected.py.graph")

if (N.isDirected()):
	print "Error: The network is directed."




