import conedy as co

co.set("samplingTime",  1.0)


net = co.network()



newNodeNumber = net.addNode(co.logisticMap())
net.setState(newNodeNumber, 0.3)
net.observe(newNodeNumber, "output/observe.py.series")

net.evolve (0.0,1000.0)






