import conedy as co



N = co.network()


N.randomNetwork(100, 0.2, co.node(),  co.weightedEdge(1.0))


print "should be close to 20:" + str( N.meanDegree() ) 
print "should be close to 0.2:" + str( N.meanClustering() ) 
