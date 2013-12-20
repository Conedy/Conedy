import conedy as co


n = co.network()

co.beeWeb(10,10)

print "Should be 6:" + n.meanDegree()
