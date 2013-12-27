import conedy as co

N = co.network()

N.addNode(co.node())
N.addNode()

N.addEdge(0,1,co.weightedEdge(0.3))
N.addEdge(1,0,staticWeightedEdge(0.3));

N.printNodeStatistics();

uN = co.undirectedNetwork()
uN.addNode(co.node())
uN.addNode()

uN.addEdge(0,1,co.weightedEdge(1.0))

print "addEdge connects nodes in undirected networks also in the opposite direction: " + uN.linkStrength (1,0);

