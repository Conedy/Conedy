import conedy as co

co.set("samplingTime", 1.0)




co.set("barkley_I", 0.1)



N = co.network()
N.lattice(1,1,1.0,co.barkley())


N.observeTime("output/barkley.py.single")
N.observeAll("output/barkley.py.single", co.component(0) )
N.observeAll("output/barkley.py.single", co.component(1) )
N.evolve(0.0,500.0)

