import conedy as co

N = co.network()

co.set ("samplingTime" , 1.0);

for i in range (0,100):
	N.addNode(co.logisticMap())

N.randomizeStates(co.logisticMap(), co.constant (0.4))
N.observeSum("output/observeSum.py.sum")

N.evolve(0.0,100.0)

