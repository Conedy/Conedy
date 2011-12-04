import conedy as co


net = co.network()


net.addNode(co.roessler())

net.setState (0, 0.1,0.2 ,0.3)

print "Should be 0.1 0.2 0.3:" + str(net.getState (0,0)) + " " + str(net.getState (0,1)) + " " + str(net.getState (0,2)) 
