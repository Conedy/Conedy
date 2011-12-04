import conedy as co
net = co.network()
bark = co.barkley()
bark.setState (0.0, 0.0)
net.lattice(512, 512, 1.0, bark)
net.rewire(0.001)
net.evolve(0.0, 20.0)
net.observeAll("waves.dat", co.component(0))
net.snapshot()
