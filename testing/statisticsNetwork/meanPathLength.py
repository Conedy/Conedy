import conedy as co

net = co.network()

net.cycle(99,1,co.node(),co.weightedEdge())
print "should be 25: " + str(net.meanPathLength()) + "\n"
