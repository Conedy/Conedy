import conedy as co

N = co.network()

co.set("kuramoto_omega", 0.1)

co.set("samplingTime", 0.01)


#just one kuramoto oscillator
firstNodeNumber = N.addNode(co.kuramoto())
N.setState(firstNodeNumber, 0.0 )
N.observeTime("output/kuramoto.py.one")
N.observe(0,"output/kuramoto.py.one", co.component(0))
N.evolve(0.0,10.0)
N.removeObserver()


#adding a second. They should synchronize.
secondNodeNumber = N.addNode(co.kuramoto())
N.addEdge (firstNodeNumber,secondNodeNumber  ,co.weightedEdge(0.1))
N.addEdge (secondNodeNumber, firstNodeNumber ,co.weightedEdge(0.1))





#small ring of oscillators. Should not synchronize.
N.setState(firstNodeNumber, 0.0 )
N.setState(secondNodeNumber, 0.3 )

N.observeTime("output/kuramoto.py.two")
N.observeAll("output/kuramoto.py.two")
N.evolve(0.0,40.0)
N.removeObserver()

thirdNodeNumber = N.addNode(co.kuramoto())
fourthNodeNumber = N.addNode(co.kuramoto())
N.addEdge ( secondNodeNumber, thirdNodeNumber ,co.weightedEdge(0.1))
N.addEdge ( thirdNodeNumber, secondNodeNumber ,co.weightedEdge(0.1))


N.addEdge ( thirdNodeNumber, fourthNodeNumber ,co.weightedEdge(0.1))
N.addEdge ( fourthNodeNumber, thirdNodeNumber ,co.weightedEdge(0.1))

N.addEdge ( fourthNodeNumber, firstNodeNumber ,co.weightedEdge(0.1))
N.addEdge ( firstNodeNumber, fourthNodeNumber ,co.weightedEdge(0.1))
N.setState(firstNodeNumber, 0.0 )
N.setState(secondNodeNumber, 0.245 )
N.setState(thirdNodeNumber, 0.495 )
N.setState(fourthNodeNumber, 0.7502 )

N.observeTime("output/kuramoto.py.ring")
N.observeAll("output/kuramoto.py.ring")
N.evolve(0.0,40.0)


