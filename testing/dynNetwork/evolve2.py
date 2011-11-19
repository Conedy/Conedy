import conedy as co

net = co.network()



co.set("samplingTime" , 10000)



nodeNumber = net.addNode(co.pcoIntegrateFire())


net.observeTime("output/snapshot.py.series")
net.observe(nodeNumber, "output/snapshot.py.series")


for i in range (0, 100):                  #observe the state of the node at times 0.3 * n
	net.evolve ( 0.3 * i, 0.3 *( i+1))
