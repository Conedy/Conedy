import conedy as co



net = co.network()


net.line(1000,1, co.node(), co.weightedEdge(1.0))  # Creates a closed chain of 100 nodes where each is connected to its 10 nearest neighbors to each side.


print "should be 1000:" + str ( net.size() )
print "should be 1.0:" + str ( net.meanWeight() )

print "should be 0.0:" + str ( net.meanClustering() ) 
print "should be 333:" + str ( net.meanPathLength() )

print "should be close to 2:" + str ( net.meanDegree() )
