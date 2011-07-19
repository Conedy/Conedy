import conedy as co


net = co.network()


net.randomNetwork(100, 0.1, co.roessler())


net.randomizeStates(co.roessler(), co.uniform (0.0,1.0), co.uniform (0.2,0.4), co.constant(0.8))

net.observeAll("output/randomizeStates.py.allStates",co.component(0))
net.observeAll("output/randomizeStates.py.allStates",co.component(1))
net.observeAll("output/randomizeStates.py.allStates",co.component(2))
net.snapshot()



