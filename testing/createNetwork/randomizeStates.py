import conedy as co


N = co.network()


N.randomNetwork(100, 0.1, co.roessler())


N.randomizeStates(co.roessler(), co.uniform (0.0,1.0), co.uniform (0.2,0.4), co.constant(0.8))

N.observeAll("output/randomizeStates.py.allStates",co.component(0))
N.observeAll("output/randomizeStates.py.allStates",co.component(1))
N.observeAll("output/randomizeStates.py.allStates",co.component(2))
N.snapshot()



