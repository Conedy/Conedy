import conedy as co

net = co.network()

co.set("kuramoto_omega", 0.1)

co.set("dynNetwork_ioNodeDt", 0.01)


#just one kuramoto oscillator
firstNodeNumber = net.addNode(co.kuramoto())
net.setState(firstNodeNumber, 0.0 )
net.observeTime("output/kuramoto.py.one")
net.observe(0,"output/kuramoto.py.one", co.component(0))
net.evolve(0.0,10.0)
net.removeObserver()


#adding a second. They should synchronize.
secondNodeNumber = net.addNode(co.kuramoto())
net.addEdge (firstNodeNumber,secondNodeNumber  ,co.weightedEdge(0.1))
net.addEdge (secondNodeNumber, firstNodeNumber ,co.weightedEdge(0.1))





#small ring of oscillators. Should not synchronize.
net.setState(firstNodeNumber, 0.0 )
net.setState(secondNodeNumber, 0.3 )

net.observeTime("output/kuramoto.py.two")
net.observeAll("output/kuramoto.py.two")
net.evolve(0.0,40.0)
net.removeObserver()

thirdNodeNumber = net.addNode(co.kuramoto())
fourthNodeNumber = net.addNode(co.kuramoto())
net.addEdge ( secondNodeNumber, thirdNodeNumber ,co.weightedEdge(0.1))
net.addEdge ( thirdNodeNumber, secondNodeNumber ,co.weightedEdge(0.1))


net.addEdge ( thirdNodeNumber, fourthNodeNumber ,co.weightedEdge(0.1))
net.addEdge ( fourthNodeNumber, thirdNodeNumber ,co.weightedEdge(0.1))

net.addEdge ( fourthNodeNumber, firstNodeNumber ,co.weightedEdge(0.1))
net.addEdge ( firstNodeNumber, fourthNodeNumber ,co.weightedEdge(0.1))
net.setState(firstNodeNumber, 0.0 )
net.setState(secondNodeNumber, 0.245 )
net.setState(thirdNodeNumber, 0.495 )
net.setState(fourthNodeNumber, 0.7502 )

net.observeTime("output/kuramoto.py.ring")
net.observeAll("output/kuramoto.py.ring")
net.evolve(0.0,40.0)


