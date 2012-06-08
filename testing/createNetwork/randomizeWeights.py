import conedy as co

N = co.network()


N.cycle( 100, 1, co.node(), co.weightedEdge())

N.randomizeWeights(co.uniform(0.0,1.50))

print "should be close to 0.75:" + str (N.meanWeight())
