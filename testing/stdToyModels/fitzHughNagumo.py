import conedy as co

co.set("dynNetwork_ioNodeDt", 1.0)




co.set("fitzHughNagumo_I", 0.1)



net = co.network()
net.lattice(1,1,1.0,co.fitzHughNagumo())


net.observeTime("output/fitzHughNagumo.py.single")
net.observeAll("output/fitzHughNagumo.py.single", co.component(0) )
net.observeAll("output/fitzHughNagumo.py.single", co.component(1) )
net.evolve(0.0,500.0)

