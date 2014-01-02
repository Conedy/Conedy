import conedy as co

N = co.network()


for i in range (0,10000):
	N.addNode (co.node ())

N.addRandomEdgesDegreeDistribution(co.uniform (0.0,100.0), co.edge()  )

N.inDegreeDistribution("output/addRandomEdgesDegreeDistribution.py.degDist")
print N.meanDegree()

