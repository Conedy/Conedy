import conedy as co



net = co.network()

newNodeNumber = net.addNode(co.logisticMap())
net.observe(newNodeNumber, "thisDirectoryDoesNotExist/observe.py.series")

net.evolve (0.0,10.0)






