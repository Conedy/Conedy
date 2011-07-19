import conedy as co

net = co.network()

net.torus (40,40,1.5, co.node(), co.weightedEdge(1.0)) #creates a torus of nodes, where each is connected to its 8 (4 direct, 4 diagonal) nearest neighbors

print "should be 8:" + str(net.meanDegree())
print "should be "+ str(12.0/28) +":" + str(net.meanClustering())

