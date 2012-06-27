#!/usr/bin/python
# coding=utf8

import conedy as co

for i in range(0,10):
	print i
	co.set("progressVerbosity", 0.0)
	co.set("odeStepSize", 0.01)
	N = co.network()
	N.addNode(co.lorenz())
	N.evolve(0, 100)
	#N.clear()
