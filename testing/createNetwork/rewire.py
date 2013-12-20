import conedy as co



N= co.network()
co.setRandomSeed(0);

node = co.roessler()
edge = co.weightedEdge(1.0)


N.cycle( 1000, 10, node,edge)


print "mean degree before rewiring:" + str( N.meanDegree())
print "should be close to 0.75:" + str( N.meanClustering())
N.rewire(1.0)
N.saveAdjacencyList("testPython")
print "mean degree after rewiring:" + str( N.meanDegree())
print "should be close to 0.0:" + str( N.meanClustering())
#print n.meanDegree()
