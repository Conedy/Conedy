import conedy as co

N = co.network()







firstNode = N.addNode(co.roessler())
secondNode = N.addNode(co.roessler())

N.addEdge (firstNode,secondNode, co.randomTarget_staticWeightedEdge (2, 100, 0.7) )


N.printNodeStatistics()

