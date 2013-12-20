import conedy as co

N = co.network()







firstNode = N.addNode(co.roessler())
secondNode = N.addNode(co.roessler())

N.addEdge (firstNode,secondNode, co.staticComponent_weightedEdge (2,3.2) )


N.printNodeStatistics()

