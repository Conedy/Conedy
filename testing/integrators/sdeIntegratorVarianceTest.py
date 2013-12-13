#!/usr/bin/python

import sys

if len(sys.argv)==1:
	# just to prevent make test printing errors
	print "no arguments given"
else:
	# to calculate the variance of the ornstein-uhlenbeck
	# the variance should be diffusion^2/(2*drift)
	file = open(sys.argv[1])
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

