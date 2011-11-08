import conedy as co


net = co.network()



co.set("ornUhl_drift" , 0.2)
co.set("ornUhl_diffusion" , 0.1)
co.set("samplingTime", 0.1)


net.addNode(co.ornUhl())
net.setState(0, 1.0)
net.observeTime("output/sdeIntegrator.py.series")
net.observeAll("output/sdeIntegrator.py.series", co.component(0))
net.evolve(0.0,15000.0)




# to calculate the variance of the ornstein-uhlenbeck
# the variance should be diffusion^2/(2*drift)
file = open('output/sdeIntegrator.py.series')
sum = 0
s2 = 0
n = 0
for line in file:
	fl = float(line.split()[1])
	sum += fl
	s2 += fl*fl
	n +=1
variance = (s2 - (sum*sum)/n)/n
print "should be around 0.025  : " +str(variance)

