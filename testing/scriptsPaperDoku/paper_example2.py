import conedy as co


co.set("pcoMirollo_a" , 0.015)
co.set("pcoMirollo_b" , 0.045)


N = co.network()
N.randomNetwork(1000, 0.01, co.pcoMirollo(),co.edge())
N.randomizeStates(co.pcoMirollo(), co.uniform(0.0, 1.0))
N.observeTime("order.dat")
N.observePhaseCoherence("order.dat")
N.evolve(0.0, 1000.0)
