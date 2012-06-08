import conedy as co

co.set("samplingTime",  1.0)


N = co.network()



newNodeNumber = N.addNode(co.logisticMap())
N.setState(newNodeNumber, 0.3)
N.observe(newNodeNumber, "output/observe.py.series")

N.evolve (0.0,1000.0)






