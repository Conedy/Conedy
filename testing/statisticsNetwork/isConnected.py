import conedy as co

N = co.network()

i = N.addNode(co.kuramoto())
j = N.addNode(co.kuramoto())

N.addEdge(j, i, co.weightedEdge(1.0))
print "should return an error: "
if( N.isConnected() ):
	print ""
print "\n"

N.clear()
N.cycle(500, 1)
print "should be connected: "
if( N.isConnected() ):
	print "connected "
print "\n"

N.addNode(co.kuramoto())
print "should be disconnected: "
if not( N.isConnected() ):
	print "disconnected "
