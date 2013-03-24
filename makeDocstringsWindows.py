#!/bin/python

from sys import argv
from os import system

beginning = argv[1].find("testing")
nameWithoutEnding = argv[1][beginning + 8:len(argv[1])- 4]
print nameWithoutEnding




system("type " + nameWithoutEnding + ".rst >" + nameWithoutEnding )
#system("echo Example:\n--------\n >>" + nameWithoutEnding )




myfile = open(nameWithoutEnding,"a") 
myfile.write("Example:\n-------\n")
myfile.close()

	
	

system ("type " + nameWithoutEnding + ".py >>" + nameWithoutEnding)
system ("xxd -i " + ".\\" + nameWithoutEnding + " >> ../docstrings.h")






