import conedy as co

N = co.network()


N.addNode (co.node())
N.addNode (co.roessler())

N.removeNodes(co.node())

print "Should be 1:" + str(N.numberVertices())
