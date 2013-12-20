import conedy as co

N = co.network()







firstNode = N.addNode(co.roessler())
secondNode = N.addNode(co.roessler())

N.addEdge (firstNode,secondNode, co.staticWeightedEdge (0.1) )
#N.addEdge (firstNode,secondNode, co.staticWeightedEdge () )
N.addEdge (secondNode,firstNode, co.staticWeightedEdge (0.2) )
# The addition of the second edge changes the coupling strength of the first edge to 0.2!


N.printNodeStatistics()

