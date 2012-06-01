import conedy as co

net = co.network()



co.set("samplingTime" , 1000.0)



nodeNumber = net.addNode(co.pcoIntegrateFire())


net.observeTime("output/evolve2.py.series")
net.observe(nodeNumber, "output/evolve2.py.series")


for i in range (0, 100):                  #observe the state of the node at times 0.3 * n
	net.evolve ( 0.03 * i, 0.03 *( i+1))
