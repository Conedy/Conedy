import conedy as co

co.setRandomSeed(0)


net= co.network()

node = co.stdRoessler()
edge = co.weightedEdge(1.0)


net.cycle( 1000, 10, node,edge)



#network_nodeVerbosity = 1.0
#network_edgeVerbosity = 2.0

#n.printNodeStatistics()

print "mean degree before rewiring:" + str( net.meanDegree())
print "should be close to 0.75:" + str( net.meanClustering())
net.rewire(1.0)
print "mean degree after rewiring:" + str( net.meanDegree())
print "should be close to 0.0:" + str( net.meanClustering())
#print n.meanDegree()
