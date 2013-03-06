import conedy as co

N=co.network()

N.cycle(100, 4, co.node(), co.weightedEdge(0.1))
N.rewireUndirected(0.3)
print "Initial mean degree:" + str(N.meanDegree())

N.removeRandomEdges(0.5, co.weightedEdge(0.1))
print "Should have changed:" + str(N.meanDegree())






