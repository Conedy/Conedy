import conedy as co



net = co.network()


net.randomNetwork(100, 0.2, co.node(),  co.weightedEdge(1.0))


print "should be close to 20:" + str( net.meanDegree() ) 
print "should be close to 0.2:" + str( net.meanClustering() ) 
