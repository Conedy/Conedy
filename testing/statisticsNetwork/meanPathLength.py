import conedy as co

N = co.network()

N.cycle(99, 1, co.node(), co.weightedEdge(0.25))
print "Should be 100: %f" % N.meanPathLength()
