import conedy as co

N = co.directedNetwork()

N.randomNetwork(100, 0.2, co.node(),  co.weightedEdge(1.0))

print "should be close to 20:" + str( N.meanDegree() ) 
print "should be close to 0.2:" + str( N.meanClustering() ) 
print "should be directed:" + str (N.isDirected())

UN = co.undirectedNetwork()

UN.randomNetwork(100, 0.2, co.node(),  co.weightedEdge(1.0))

print "should be close to 20:" + str( UN.meanDegree() ) 
print "should be close to 0.2:" + str( UN.meanClustering() ) 
print "should be undirected:" + str (UN.isDirected())

