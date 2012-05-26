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

co.set("network_nodeVerbosity" ,1.0)
co.set("network_edgeVerbosity" ,0.0)
print "nodeVerbosity =1.0, edgeVerbosity=0.0"+"\n"
print "-------------------------------------"+"\n"
net.printNodeStatistics()
print"\n"
print"\n"

co.set("network_nodeVerbosity" ,2.0)
co.set("network_edgeVerbosity" ,0.0)
print "nodeVerbosity =2.0, edgeVerbosity=0.0"+"\n"
print "-------------------------------------"+"\n"
net.printNodeStatistics()
print"\n"
print"\n"



net.addNode(co.roessler())
net.addEdge(0,1,co.weightedEdge(1.0))

co.set("network_nodeVerbosity" ,2.0)
co.set("network_edgeVerbosity" ,1.0)
print "nodeVerbosity =2.0, edgeVerbosity=1.0"+"\n"
print "-------------------------------------"+"\n"
net.printNodeStatistics()
print"\n"
print"\n"

co.set("network_nodeVerbosity" ,2.0)
co.set("network_edgeVerbosity" ,2.0)
print "nodeVerbosity =2.0, edgeVerbosity=2.0"+"\n"
print "-------------------------------------"+"\n"
net.printNodeStatistics()
print"\n"
print"\n"


