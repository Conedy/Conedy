import conedy as co

net = co.network()

net.addNode(co.kuramoto())


print "kuramoto_omega:" + str ( net.getParam(0,"kuramoto_omega"))

