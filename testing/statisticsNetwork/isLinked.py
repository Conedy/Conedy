
import  conedy as co


net = co.network()

source = net.addNode(co.node())
target = net.addNode(co.node())
net.addEdge (source,target, co.weightedEdge(1.0))

print "Should be true:" + str(net.isLinked (source,target))
print "Should be false:" + str(net.isLinked (target,source))
