
import conedy as co

N = co.network()

newNodeNumber = N.addNode(co.logisticMap())
N.observe(newNodeNumber, "output/setState.py.state")
N.setState(newNodeNumber, 0.3)


newNodeNumber = N.addNode(co.roessler())
N.setState(newNodeNumber, 0.1,0.2,0.25)


N.observe(newNodeNumber, "output/setState.py.state",co.component(0))
N.observe(newNodeNumber, "output/setState.py.state",co.component(1))
N.observe(newNodeNumber, "output/setState.py.state",co.component(2))

N.snapshot()
