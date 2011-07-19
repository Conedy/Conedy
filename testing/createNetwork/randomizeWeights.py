import conedy as co

net = co.network()


net.cycle( 100, 1, co.node(), co.weightedEdge())

net.randomizeWeights(co.uniform(0.0,1.50))

print "should be close to 0.75:" + str (net.meanWeight())
