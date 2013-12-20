import conedy as co

N = co.network()



co.set("samplingTime" , 1000.0)



nodeNumber = N.addNode(co.pcoIntegrateFire())


N.observeTime("output/evolve2.py.series")
N.observe(nodeNumber, "output/evolve2.py.series")


for i in range (0, 100):                  #observe the state of the node at times 0.3 * n
	N.evolve ( 0.03 * i, 0.03 *( i+1))
