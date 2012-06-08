import conedy as co

fehlerzahl = 0

for combo in [
	("samplingTime", "blue"),
	("samplingTime", 1),
	("samplingTime", True),
	("samplingTime", 10.0),
	("odeIsAdaptive", "Horst"),
	("odeIsAdaptive", 3.14),
	("odeIsAdaptive", True),
	("odeStepType", 42),
	("odeStepType", 2.72),
	("odeStepType", True),
	("odeStepType", "gsl_odeiv_step_rk8pd"),
	("outputPrecision", 1.41),
	("outputPrecision", "Fisch"),
	("outputPrecision", 12)
	]:
	try:
		co.set(combo[0], combo[1])
	except:
		fehlerzahl += 1

print "Should be 10: %i" % fehlerzahl
