import conedy as co

N = co.network()


N.addNode(co.roessler())
print "Should be 1:" + str (N.numberVertices())
N.clear()
print "Should be 0:" + str (N.numberVertices())

