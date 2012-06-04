import conedy as co

N = co.network()

N.addNode(co.kuramoto())


print "kuramoto_omega:" + str ( N.getParam(0, "kuramoto_omega"))

