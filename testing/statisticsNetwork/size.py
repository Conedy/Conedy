import conedy as co

net = co.network()

net.lattice(40,40,1.5,co.node(),co.weightedEdge())
print "should be 1600: " + str(net.size())

net.clear()
net.cycle(50,3, co.node(),co.weightedEdge() )
print "should be 50: " + str(net.size())

