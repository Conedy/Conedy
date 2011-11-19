import conedy as co

net = co.network()







firstNode = net.addNode(co.roessler())
secondNode = net.addNode(co.roessler())

net.addEdge (firstNode,secondNode, co.staticWeightedEdge (0.1) )
#net.addEdge (firstNode,secondNode, co.staticWeightedEdge () )
net.addEdge (secondNode,firstNode, co.staticWeightedEdge (0.2) )
# The addition of the second edge changes the coupling strength of the first edge to 0.2!


net.printNodeStatistics()

