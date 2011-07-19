import conedy as co


net = co.network()


net.randomNetwork(100, 0.1, co.roessler())


net.randomizeParameter ("roessler_omega", co.uniform (0.80, 0.85))


for i in range (0,100):
	print "Node " + str (i)+ ":"+ str(net.getParam(i, "roessler_omega"))







