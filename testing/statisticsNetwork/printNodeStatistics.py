import conedy as co



net = co.network()

net.addNode(co.roessler())


co.set("nodeVerbosity" ,0)
co.set("edgeVerbosity" ,0)


print "nodeVerbosity =0.0, edgeVerbosity=0.0"+"\n"
print "-------------------------------------"+"\n"
net.printNodeStatistics()
print"\n"
print"\n"

co.set("nodeVerbosity" ,1)
co.set("edgeVerbosity" ,0)
print "nodeVerbosity =1.0, edgeVerbosity=0.0"+"\n"
print "-------------------------------------"+"\n"
net.printNodeStatistics()
print"\n"
print"\n"

co.set("nodeVerbosity" ,2)
co.set("edgeVerbosity" ,0)
print "nodeVerbosity =2.0, edgeVerbosity=0.0"+"\n"
print "-------------------------------------"+"\n"
net.printNodeStatistics()
print"\n"
print"\n"



net.addNode(co.roessler())
net.addEdge(0,1,co.weightedEdge(1.0))

co.set("nodeVerbosity" ,2)
co.set("edgeVerbosity" ,1)
print "nodeVerbosity =2.0, edgeVerbosity=1.0"+"\n"
print "-------------------------------------"+"\n"
net.printNodeStatistics()
print"\n"
print"\n"

co.set("nodeVerbosity" ,2)
co.set("edgeVerbosity" ,2)
print "nodeVerbosity =2.0, edgeVerbosity=2.0"+"\n"
print "-------------------------------------"+"\n"
net.printNodeStatistics()
print"\n"
print"\n"


