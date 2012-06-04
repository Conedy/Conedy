import conedy as co

N = co.network()

N.torus (40,40,1.5, co.node(), co.weightedEdge(1.0)) #creates a torus of nodes, where each is connected to its 8 (4 direct, 4 diagonal) nearest neighbors

print "should be 8:" + str(N.meanDegree())
print "should be "+ str(12.0/28) +":" + str(N.meanClustering())

