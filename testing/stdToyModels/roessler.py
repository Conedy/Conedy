import conedy as co


net = co.network()

co.set("roessler_omega" , 0.89)
co.set("roessler_a" , 0.165)
co.set("roessler_b" , 0.2)
co.set("roessler_c" , 10.0)
co.set("samplingTime" , 0.01)



net.addNode(co.roessler())
net.setState(0, 0.0, 0.0, 0.0)
net.observeTime("output/roessler.py.series")
net.observeAll("output/roessler.py.series", co.component(0))
net.observeAll("output/roessler.py.series", co.component(1))
net.observeAll("output/roessler.py.series", co.component(2))


net.evolve(0.0,1500.0)
