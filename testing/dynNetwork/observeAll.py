import conedy as co

N = co.network()

N.randomNetwork (10,0.1,co.kuramoto(), co.weightedEdge())

N.observeAll ("output/observeAll.allStates")


for i in range (0,10):
	N.observe (i, "output/observeAll.allStates2")


N.evolve(0.0,10.0)


