import conedy as co

net = co.network()







firstNode = net.addNode(co.roessler())
secondNode = net.addNode(co.roessler())

net.addEdge (firstNode,secondNode, co.component_staticWeightedEdge (2) )
net.randomizeWeights(co.constant(0.1))


net.printNodeStatistics()

