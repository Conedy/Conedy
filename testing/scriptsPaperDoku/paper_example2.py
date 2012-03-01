import conedy as co


co.set("pcoMirollo_a" , 0.015)
co.set("pcoMirollo_b" , 0.045)


net = co.network()
net.randomNetwork(1000, 0.01, co.pcoMirollo(),co.edge())
net.randomizeStates(co.pcoMirollo(), co.uniform(0.0, 1.0))
net.observeTime("order.dat")
net.observePhaseCoherence("order.dat")
net.evolve(0.0, 1000.0)
