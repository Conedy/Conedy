#!/usr/bin/python
# coding=utf8

import conedy as co

def foo():
	N = co.network()
	N.addNode(co.lorenz())
	N.evolve(0, 100)



for i in range(0,10):
	print i
	co.set("progressVerbosity", 0.0)
#	co.set("stepSize", 0.01)
	foo()
	#N.clear()
