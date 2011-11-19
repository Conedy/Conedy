import conedy as co

co.set("samplingTime", 1.0)




co.set("barkley_I", 0.1)



net = co.network()
net.lattice(1,1,1.0,co.barkley())


net.observeTime("output/barkley.py.single")
net.observeAll("output/barkley.py.single", co.component(0) )
net.observeAll("output/barkley.py.single", co.component(1) )
net.evolve(0.0,500.0)

