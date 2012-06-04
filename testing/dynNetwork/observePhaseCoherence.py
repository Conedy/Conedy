import conedy as co

N = co.network()


N.cycle(10,1,co.kuramoto())


N.observePhaseCoherence("output/observePhaseCoherence.py.1")
N.evolve(0.0,10.0)
N.removeObserver()


for i in range (0, 10):
	N.setState(i, i/10.0)


N.observePhaseCoherence("output/observePhaseCoherence.py.0")
N.evolve(10.0,20.0)


