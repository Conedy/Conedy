import conedy as co


N = co.network()

N.completeNetwork(10) # adds 10 nodes, which are mutually connected by unweighted edges


print "should be 9:" + str(N.meanDegree())
print "should be 1.0:" + str(N.meanClustering())
print "should be 1.0:" + str(N.meanPathLength())
