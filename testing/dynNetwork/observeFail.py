import conedy as co



N = co.network()

newNodeNumber = N.addNode(co.logisticMap())
N.observe(newNodeNumber, "thisDirectoryDoesNotExist/observe.py.series")

N.evolve (0.0,10.0)






