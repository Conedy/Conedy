import conedy as co



N = co.network()

newNodeNumber = N.addNode(co.logisticMap())

#N.printNodeStatistics()
N.observe(newNodeNumber+1, "output/observe.py.series")


N.evolve (0.0,10.0)






