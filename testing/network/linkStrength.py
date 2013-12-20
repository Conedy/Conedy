import conedy as co

N = co.network()

N.addNode(co.node())
N.addNode()

N.addWeightedEdge(0,1,0.7)

print "Should be 0.7:" + N.linkStrength (0,1);

