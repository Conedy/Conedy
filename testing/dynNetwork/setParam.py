import conedy as co

N = co.network()

nodeNumber = N.addNode (co.roessler())

N.setParam (nodeNumber, "roessler_omega", 0.92)


print "Should be 0.92:" + str(N.getParam(nodeNumber, "roessler_omega"))
