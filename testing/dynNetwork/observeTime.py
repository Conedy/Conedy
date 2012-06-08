import conedy as co


N = co.network()

co.set("samplingTime" , 0.015)



N.observeTime("output/observeTime.py.time")


N.evolve(0.0,10.0)
