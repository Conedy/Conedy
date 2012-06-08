import conedy as co
N = co.network()
co.set ("gaussianBarkley_sigma",  0.18)

bark = co.gaussianBarkley()
bark.setState (0.0, 0.0)
N.lattice(512, 512, 1.0, bark, co.staticWeightedEdge (3.84))
N.rewire(0.001)
N.evolve(0.0, 20.0)
N.observeAll("waves.dat", co.component(0))
N.snapshot()
