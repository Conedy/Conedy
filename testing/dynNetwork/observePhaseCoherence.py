import conedy as co

net = co.network()


net.cycle(10,1,co.kuramoto())


net.observePhaseCoherence("output/observePhaseCoherence.1")
net.evolve(0.0,10.0)
net.removeObserver()


for i in range (0, 10):
	net.setState(i, i/10.0)


net.observePhaseCoherence("output/observePhaseCoherence.0")
net.evolve(10.0,20.0)


