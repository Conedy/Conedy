import conedy as co


N = co.network()

N.completeNetwork(10)  # creates a Nwork of 10 nodes, where every pair is connected by an unweighted edge
print "Should be 9: " + str (N.meanDegree())


N.clear()
N.cycle(50, 3, co.node(), co.weightedEdge())
N.rewire(0.9)
print "Should be 6: " + str (N.meanDegree())
