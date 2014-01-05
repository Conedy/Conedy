import conedy as co

n = co.network()



n.addNode (co.node())

n.removeNodes (co.roessler())

print "Should be 1:" + str(n.numberVertices())

n.replaceNode (0, co.roessler())
n.removeNodes (co.roessler())

print "Should be 0:" + str(n.numberVertices())
