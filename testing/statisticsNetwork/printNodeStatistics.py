import conedy as co

N = co.network()
i = N.addNode(co.roessler())

co.set("nodeVerbosity", 0)
co.set("edgeVerbosity", 0)
print "nodeVerbosity = 0, edgeVerbosity = 0\n"
print "------------------------------------\n"
N.printNodeStatistics()
print"\n\n"

co.set("nodeVerbosity", 1)
co.set("edgeVerbosity", 0)
print "nodeVerbosity = 1, edgeVerbosity = 0\n"
print "------------------------------------\n"
N.printNodeStatistics()
print"\n\n"

co.set("nodeVerbosity", 2)
co.set("edgeVerbosity", 0)
print "nodeVerbosity = 2, edgeVerbosity = 0\n"
print "------------------------------------\n"
N.printNodeStatistics()
print"\n\n"



j = N.addNode(co.roessler())
N.addEdge(i, j, co.weightedEdge(1.0))

co.set("nodeVerbosity", 2)
co.set("edgeVerbosity", 1)
print "nodeVerbosity = 2, edgeVerbosity = 1\n"
print "------------------------------------\n"
N.printNodeStatistics()
print"\n\n"

co.set("nodeVerbosity", 2)
co.set("edgeVerbosity", 2)
print "nodeVerbosity = 2, edgeVerbosity = 2\n"
print "------------------------------------\n"
N.printNodeStatistics()
print"\n\n"


