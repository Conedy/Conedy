import conedy as co

N = co.network()

N.torusNearestNeighbors (40,40,36.0, co.node(), co.weightedEdge()) #creates a torus of nodes, where each is connected to its 8 (4 direct, 4 diagonal) nearest neighbors and to 2 neighbors with distance 2 randomly chosen

print "should be 36.0:" + str(N.meanDegree()) 

