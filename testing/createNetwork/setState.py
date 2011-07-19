
import conedy as co

net = co.network()

newNodeNumber = net.addNode(co.logisticMap())
net.observe(newNodeNumber, "output/setState.py.state")
net.setState(newNodeNumber, 0.3)


newNodeNumber = net.addNode(co.roessler())
net.setState(newNodeNumber, 0.1,0.2,0.25)


net.observe(newNodeNumber, "output/setState.py.state",co.component(0))
net.observe(newNodeNumber, "output/setState.py.state",co.component(1))
net.observe(newNodeNumber, "output/setState.py.state",co.component(2))

net.snapshot()
