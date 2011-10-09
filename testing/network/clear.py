import conedy as co

net = co.network()


net.addNode(co.roessler())
print "Should be 1:" + str (net.size())
net.clear()
print "Should be 0:" + str (net.size())

