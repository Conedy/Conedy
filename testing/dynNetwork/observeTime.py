import conedy as co


net = co.network()

co.set("samplingTime" , 0.015)



net.observeTime("output/observeTime.py.time")


net.evolve(0.0,10.0)
