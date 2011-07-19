import conedy as co


net = co.network()

net.completeNetwork(10)  # creates a network of 10 nodes, where every pair is connected by an unweighted edge
print "Should be 9: " + str (net.meanDegree())

net.clear()
net.cycle(50,3,co.node(),co.weightedEdge())
print "Should be 6: " + str (net.meanDegree())
