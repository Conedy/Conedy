import conedy as co

N = co.network()

N.addNode(co.node())
N.addNode()

N.addEdge(0,1,co.weightedEdge(0.3))
N.addEdge(1,0,co.staticWeightedEdge(0.2))

N.printNodeStatistics()

uN = co.undirectedNetwork()
sourceNode = uN.addNode(co.node())
targetNode = uN.addNode()

#addEdge connects nodes in undirected networks also in the opposite direction.
uN.addEdge(sourceNode,targetNode,co.weightedEdge(1.0))


print "linkStrength (should be 1.0):" + str(uN.linkStrength (targetNode,sourceNode))

