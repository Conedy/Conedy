import conedy as co



N = co.network()


N.line(1000,1, co.node(), co.weightedEdge(1.0))  # Creates a closed chain of 100 nodes where each is connected to its 10 nearest neighbors to each side.


print "should be 1000:" + str ( N.numberVertices() )
print "should be 1.0:" + str ( N.meanWeight() )

print "should be 0.0:" + str ( N.meanClustering() ) 
print "should be 333:" + str ( N.meanPathLength() )

print "should be close to 2:" + str ( N.meanDegree() )
