import conedy as co

net = co.network()

net.randomNetwork(100, 0.2, co.node(), co.weightedEdge())

net.randomizeWeights(co.uniform (0.0,1.5))

print "Should be close to 0.75:" + str(net.meanWeight())


