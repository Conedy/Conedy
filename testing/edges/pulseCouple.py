import conedy as co

net = co.network()







firstNode = net.addNode(co.fitzHughNagumo())
secondNode = net.addNode(co.fitzHughNagumo())

net.addEdge (firstNode,secondNode, co.pulseCouple (1.0) )


net.printNodeStatistics()

