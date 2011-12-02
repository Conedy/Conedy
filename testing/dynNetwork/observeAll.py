import conedy as co

net = co.network()

net.randomNetwork (10,0.1,co.kuramoto(), co.weightedEdge())

net.observeAll ("output/observeAll.allStates")


for i in range (0,10):
	net.observe (i, "output/observeAll.allStates2")


net.evolve(0.0,10.0)


