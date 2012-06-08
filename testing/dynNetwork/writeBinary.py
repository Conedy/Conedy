import conedy as co





N = co.network()

co.set("outputBinary", bool (1))
co.set("samplingTime" , 0.015)



N.observeTime("output/writeBinary.py.time")


#N.printNodeStatistics()

N.evolve(0.0,10.0)
