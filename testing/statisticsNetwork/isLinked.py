import conedy as co


N = co.network()

source = N.addNode(co.node())
target = N.addNode(co.node())
N.addEdge (source, target, co.weightedEdge(1.0))

print "Should be True: " + str(N.isLinked (source,target))
print "Should be Talse: " + str(N.isLinked (target,source))
