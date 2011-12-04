import conedy as co



net = co.network()

newNodeNumber = net.addNode(co.logisticMap())

#net.printNodeStatistics()
net.observe(newNodeNumber+1, "output/observe.py.series")


net.evolve (0.0,10.0)






