import conedy as co
net = co.network()
net.randomNetwork(10000, 0.001, co.pcoMirollo(),co.weightedEdge(0.08))
net.randomizeStates(co.pcoMirollo(), co.uniform(0.0, 1.0))
net.observeTime("order.dat")
net.observePhaseCoherence("order.dat")
net.evolve(0.0, 1000.0)
