import conedy as co

net = co.network()



net.cycle(100,3, co.node(), co.weightedEdge() )




print "should be 6:" + str (net.meanDegree())
net.rewireUndirected(1.0)
print "should be 6:" + str (net.meanDegree())

print "should be false: " + str(net.isDirected())

