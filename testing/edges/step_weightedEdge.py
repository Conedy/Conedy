import conedy as co

net = co.network()







firstNode = net.addNode(co.roessler())
secondNode = net.addNode(co.roessler())

net.addEdge (firstNode,secondNode, co.step_weightedEdge (0.5) )


net.printNodeStatistics()

