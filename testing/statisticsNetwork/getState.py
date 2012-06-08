import conedy as co

N = co.network()

i = N.addNode(co.roessler())

N.setState (0, 0.1, 0.2 ,0.3)

print "Should be 0.1 0.2 0.3:" + str(N.getState (i,0)) + " " + str(N.getState (i,1)) + " " + str(N.getState (i,2))
