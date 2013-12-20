import conedy as co
from os import system


n = co.network()


networkSize = 10

n.randomNetwork( networkSize, 0.4, co.node(), co.weightedEdge())
n.randomizeWeights (co.uniform (1.1,1.1))

n.saveAdjacencyList("output/normalizeInputs.co.before")
n.normalizeInWeightSum (3.0)

print "Should be "+ 3.0/n.meanDegree()+" :"+n.meanWeight()

n.saveAdjacencyList("output/normalizeInputs.co.after")


system ("sort -n output/normalizeInputs.co.after -k2 > output/normalizeInputs.co.after.sort")
