import conedy as co

net = co.network()

net.addNode(co.kuramoto())
net.addNode(co.kuramoto())

net.addEdge(1,0, co.weightedEdge(1.0))
print "should give an error: "
if( net.isConnected() ):
	print ""
print "\n"

net.clear()
net.cycle(500,1)
print "should be connected: "
if( net.isConnected() ):
	print "connected "
print "\n"

net.addNode(co.kuramoto())
print "should be disconnected: "
if not( net.isConnected() ):
	print "disconnected "
