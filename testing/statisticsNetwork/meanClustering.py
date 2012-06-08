import conedy as co

N = co.network()

N.cycle(100,4)
print "Should be close to %f: %f" % (9./14, N.meanClustering())


N.clear()
N.torus (40, 40, 1.5, co.node(), co.weightedEdge(1.0))
print "Should be close to %f: %f" % (6./14, N.meanClustering())

