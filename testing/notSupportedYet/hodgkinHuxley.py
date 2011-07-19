import conedy as co

co.set("dynNetwork_ioNodeDt", 0.02)

co.set("hodgkinHuxley_I", 20.0)


net = co.network()
net.lattice(1,1,1.0,co.hodgkinHuxley())


net.observeTime("output/hodgkinHuxley.co.single")
net.observeAll("output/hodgkinHuxley.co.single",co.component(0))
net.observeAll("output/hodgkinHuxley.co.single",co.component(1))
net.evolve(0.0,500.0)

