import conedy as co

N = co.network()


N.cycle ( 1000, 10, roessler(), weightedEdge(1.0));


print "mean degree before rewiring:" + str(N.meanDegree()
print "should be close to 0.75:" +  str( N.meanClustering())
N.replaceEdges(1.0, staticWeightedEdge(0.2));
print "mean degree after rewiring:" +  str(N.meanDegree())
print "should be close to 0.0:" +  str(N.meanClustering())

N.printNodeStatistics();



