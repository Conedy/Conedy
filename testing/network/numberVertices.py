import conedy as co

N = co.network()

N.lattice(40, 40, 1.5, co.node(),co.weightedEdge())
print "should be 1600: " + str(N.numberVertices())

N.clear()
N.cycle(50, 3, co.node(), co.weightedEdge() )
print "should be 50: " + str(N.numberVertices())

