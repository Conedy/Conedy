import conedy as co


N = co.network()


N.randomNetwork(100, 0.1, co.roessler())


N.randomizeParameter ("roessler_omega", co.uniform (0.80, 0.85))


for i in range (0,100):
	print "Node " + str (i)+ ":"+ str(N.getParam(i, "roessler_omega"))







