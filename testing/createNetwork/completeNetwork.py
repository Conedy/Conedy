import conedy as co


net = co.network()

net.completeNetwork(10) # adds 10 nodes, which are mutually connected by unweighted edges


print "should be 9:" + str(net.meanDegree())
print "should be 1.0:" + str(net.meanClustering())
print "should be 1.0:" + str(net.meanPathLength())
