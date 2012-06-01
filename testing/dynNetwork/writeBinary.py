import conedy as co





net = co.network()

co.set("outputBinary", bool (1))
co.set("samplingTime" , 0.015)



net.observeTime("output/writeBinary.py.time")


#net.printNodeStatistics()

net.evolve(0.0,10.0)
