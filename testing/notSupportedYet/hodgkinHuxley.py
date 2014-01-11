import conedy as co

co.set("samplingTime", 0.02)

co.set("hodgkinHuxley_I", 20.0)


N = co.network()
N.lattice(1,1,1.0,co.hodgkinHuxley())


N.observeTime("output/hodgkinHuxley.co.single")
N.observeAll("output/hodgkinHuxley.co.single",co.component(0))
N.observeAll("output/hodgkinHuxley.co.single",co.component(1))
N.evolve(0.0,500.0)

