import conedy as co

net =co.network()

net.cycle(20,1,co.node(), co.weightedEdge() )

net.addEdge(1,7,co.weightedEdge(1.0) )
net.addEdge(7,1,co.weightedEdge(1.0) )
net.addEdge(1,11,co.weightedEdge(1.0) )
net.addEdge(11,1,co.weightedEdge(1.0) )


net.degreeCentrality("output/degreeCentrality.py.out")
