import conedy as co

net = co.network()

net.cycle(100,4)
print "should be close to"+ str(18.0/28) +": " + str(net.meanClustering())

net.clear()
net.torus (40,40,1.5, co.node(), co.weightedEdge(1.0))
print "should be close to"+ str(12.0/28) +": " + str(net.meanClustering())

