import conedy as co

N = co.network()

N.randomNetwork(100, 0.2, co.node(), co.weightedEdge())

N.randomizeWeights(co.uniform (0.0, 1.5))

print "Should be close to 0.75:" + str(N.meanWeight())


