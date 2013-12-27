import conedy as co

N = co.network()

N.addNode (co.node())

print "Should be 0:" + str(N.degree(0))
N.addEdge (0,0)
print "Should be 1:" + str(N.degree(0))
