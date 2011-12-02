import conedy as co

net = co.network()

nodeNumber = net.addNode (co.roessler())

net.setParam (nodeNumber, "roessler_omega", 0.92)


print "Should be 0.92:" + str(net.getParam(nodeNumber, "roessler_omega"))
