import conedy as co

N = co.network()



firstNode = N.addNode(co.roessler())
secondNode = N.addNode(co.roessler())

N.addEdge (firstNode,secondNode,  co.edge() )


N.printNodeStatistics()

