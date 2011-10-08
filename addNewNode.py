#
#    Neurosim is a scientific tool which allows numerical integration of dynamical networks.
#
#    Copyright (C) 2011 Alexander Rothkegel, Henning Dickten, Ferdinand Stolz, Justus Schwabedahl
#
#    This file is part of conedy.
#
#    Neurosim is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>


#!/usr/bin/python
# -*- coding: utf8 -*-


#TODO: addNewNode.py shouldn't be mad about upper case parameter names ?


import os
import sys
import ConfigParser

import re

def cleanString(stringIn):
	"Erstellt einen CamelCaseString und entfernt alle Leerzeichen."
	return stringIn.title().replace(" ", "").replace("-","_").strip("_").rstrip("_")

def underline(stringIn):
	print stringIn
	print len(stringIn)*"-"

class NodeEditor:

	className = ""
	nodeInfo = ""
	params = []
	events = []
	functions = [ "getWeightedSum()", "getCouplingSum()", "getWeighedInSum()" ]
	dgl = []
	upkeep = []
	doku = []
	dim = 0
	numParam = 0
	shortDescription = "short description ..."
	longDescription  = "long description ..."
	integrator = ""
	staticEdges = 0
	staticEdgeType = ""
	staticTargetNodeType = ""
	fileNameOut = ""


#	def __init__ (self):
		

	def readConsole(self,inName="", inDim=-1, integrator = "",   events = [],inNumParam=-1, params = [], dgl = [], doku = [], staticEdges = 0, staticEdgeType = "", staticTargetNodeType= "", inFileNameOut=""):

		"Klasse zum Erstellen neues Nodes in Neurosim"

		self.events = events
		self.params = params
		self.doku = doku

		# Klassenname einlesen
		if (inName == ""):
			temp = raw_input("Please enter new nodename: ")
			print "\n"
		else:
			temp = inName
	

		self.className = temp
		self.nodeInfo  = "_" + self.className + "_" 


		# Integrator enlesen
	
		if (integrator == ""):
			temp = raw_input("Please choose an nodeType (integrator) from the following list\n\todeNode, stdSdeIntegrator, stdOdeIntegrator, pcoBase, pcoDelay , mapNode: ")
			print "\n"
			self.integrator = temp
		else:
			self.integrator = integrator

		# Dimension des Oszillators abfragen
		while (inDim <= 0):
			inDim = int(raw_input("Please enter dimension of oszillator ( >= 1 ): "))
			print "\n"
		self.dim		= inDim


		# Anzahl der Parameter abfragen
		while (inNumParam < 0):
			inNumParam = int(raw_input("Please enter number of dynamic parameters: ( >= 0 ): "))
			print "\n"
		self.numParam	= inNumParam


		# Parameter abfragen
		
		
		if (static == 1):
			self.static = 1
			self.staticEdgeType = staticEdgeType
			self.staticTargetNodeType = staticTargetNodeType


		while  len(self.params) < self.numParam:
			self.addNewParam(len(self.params)+1)
			print "\n"

		# DGL abfragen
		if (dgl == []):
			underline("Dynamic of %s dim. oszillator:" % self.dim)
			print "\n"
			
			print "AVAILABLE FUNCTIONS:\n"
			for f in self.functions:
				print f
			print "\n"
	
			print "AVAILABLE PARAMETERS:\n"
			for p in self.params:
				print p[0] + "()\t",
			print "\n\n"
	
			if (len(self.params) > 0):
				print "EXAMPLE: dxdt[0] = %s()*x[0] + x[1]**2 + CS - WS*x[0]\n\n" % self.params[0][0]
			else:
				print "EXAMPLE: dxdt[0] = 1/2*x[0] + x[1]**2 + CS - WS*x[0]\n\n"
	
			
	
			if self.integrator == "stdOdeIntegrator":
				for d in range(self.dim):
					temp = "dxdt[" + str(d) + "] = "
					self.dgl.append(temp + raw_input(temp))
			elif self.integrator =="mapNode":
				for d in range(self.dim):
					temp = "xprime[" + str(d) + "] = "
					self.dgl.append(temp + raw_input(temp))
			else:
				raise Exception('spam', 'eggs')
		else:
			self.dgl = dgl

		# Rest der Eingabe ist Doku

		if (self.doku == []):
			temp = raw_input("Doku:")
			self.doku.append(temp)
			while temp != "":
				temp = raw_input("Doku:") # TODO hier waere es viel sinnvoller auf EOF zu ueberpruefen. Leider weiss ich grad nicht, wie das geht.
				self.doku.append(temp)
	


	def addNewParam(self, pNum):
		"Fuegt den n.ten Parameter hinzu"

		paramName = raw_input("Please enter %i. parameter name: " % pNum)
		paramName = cleanString(paramName)
		paramName = paramName[0].lower() + paramName[1:]

		paramDefault = float( raw_input("Please enter default value of \"%s\": " % paramName) )

		self.params.append( (paramName, paramDefault) )




	def writeHeaderFile(self):
		"writes the header file"
		
		
		try:         
			fin = open(".countAddedNodes" , 'r')
			theString = fin.readline()
			self.numberAddedNodes = int(theString)
			fin.close()
		except:
			self.numberAddedNodes = 0
		
		self.numberAddedNodes = self.numberAddedNodes + 1

		fileNameOut = self.nodeInfo[1:-1]

		fout = open("generated" + self.className + ".h", 'w')

		# Header schreiben
		fout.write("#ifndef %s_h\n#define %s_h %s_h\n\n#include <math.h>\n\n" % (fileNameOut, fileNameOut, fileNameOut))
		fout.write("#include \"baseType.h\"\n")
		fout.write("#include \"sdeNode.h\"\n")
		fout.write("#include <boost/function.hpp>\n\n")


		# Integrator festlegen
		fout.write("// Integrator waehlen\n#include \"%s.h\"\n\n" % self.integrator)

		# Beschreibung
		fout.write("namespace conedy\n{\n")

		if (self.numberAddedNodes < 10):
			fout.write("const networkElementType " + self.nodeInfo + "= 10" + str(self.numberAddedNodes) + ";\n")
		else:
			fout.write("const networkElementType " + self.nodeInfo + "= 1" + str(self.numberAddedNodes) + ";\n")
		fout.write("/**\n * \\brief  %s\n" % self.shortDescription)

		for d in self.doku:
			fout.write(" * " +d)
		fout.write(" *\n * %s\n *\n" % self.longDescription )
		fout.write(" *\n")
		
		fout.write(" * Usage (conedy):\n")
		fout.write(" * n.addNode< " + self.className + "( ")
		i = 1
		for p in self.params:
			fout.write(str(p[1]))
			if (i < len(self.params)):
				fout.write(", ")
				i+=1
		del i
		fout.write(" ) >();\n")

		fout.write(" * \n")
		
		# Parameter beschreiben
		for p in self.params:
			fout.write(" * \\param	" + p[0] + "() \tdefault Value: " + str(p[1]) + ",\tadd description here ...\n")
		fout.write(" *\n **/\n")


		# Klasse erstellen
		fout.write("class %s : public %s" %( self.className, self.integrator))

		if (len (self.events) > 0):   # derive from eventHandler if events are specified
			fout.write(", public eventHandler\n")

		fout.write("\n\t{\n")
		
		fout.write("\tprivate:\n")
		
		# Parameter erstellen
		fout.write("\t\t//! Inlinefunktionen zur einfacheren Verwaltung der %i Parameter\n" %	len(self.params))
		i = 0

		if self.integrator == "pcoBase":
			i = 2
		elif self.integrator =="pcoDelay":
			i = 3

		for p in self.params:
			fout.write("\t\tinline baseType %s()	{ return params<baseType>::getParams(%i); }\n" % ( p[0], i) )
			i+=1
		fout.write("\t\t\n")

		fout.write("\tpublic:\n")
	
		if (self.upkeep != ""):


			dyn = self.upkeep       #replace all parameter by the inline functions 
			for p in self.params:
				dyn = re.sub ("\\b" + p[0] + "\\b", p[0] + "()", dyn)

			self.upkeep = dyn




			fout.write ("\t\tvirtual bool requiresUpkeep() { return true;}\n")
			fout.write ("\t\tvirtual void upkeep (); \n")

		if (len (self.events) > 0):
			fout.write("\t\tvirtual unsigned int numberOfEvents() const { return %i;}\n" % len(self.events))

			fout.write("\t\tvirtual baseType callBack ( unsigned int eventSignature ); \n")
	
			fout.write("\t virtual ~%s ();" % self.className)		
			fout.write("\t %s ( const %s &b); " %(self.className, self.className))

		fout.write("\t\t//! Konstruktor ohne Parameter\n")
		fout.write("\t\t%s() : %s(%s) {}\n" % (self.className, self.integrator, self.nodeInfo) )
		fout.write("\t\t\n")

		fout.write("\t\t//! Liefert die Dimension der Node zurueck\n")
		fout.write("\t\tvirtual const unsigned int dimension() const { return %i;}\n" % self.dim)
		fout.write("\t\t\n")


		if self.integrator == "stdOdeIntegrator":
			fout.write("\t\t//! Interface for ODE \n")
			fout.write("\t\tvirtual void operator() (const baseType  x[], baseType  dydx[]);\n")
			fout.write("\t\t\n")
		elif self.integrator =="pcoBase":
			fout.write("\t\t//! Interface for pco\n") 
			fout.write("\t\tvirtual baseType phaseResponse(baseType coupling, baseType phi);\n")
			fout.write("\t\t\n")
		elif self.integrator =="pcoDelay":
			fout.write("\t\t//! Interface for pco\n") 
			fout.write("\t\tvirtual baseType phaseResponse(baseType coupling, baseType phi);\n")
			fout.write("\t\t\n")
		elif self.integrator =="mapNode":
			fout.write("\t\t//! Interface for map\n")
			fout.write("\t\tvirtual void operator() (baseType xprime [], baseType x[]);\n")
			fout.write("\t\t\n")
		elif self.integrator =="stdSdeIntegrator":
			fout.write("\t\t//! Interface for SDE\n")
			fout.write("virtual void operator()(baseType x[], baseType  dxdt[], baseType s[], baseType dsdx[]);\n")
			fout.write("\t\t\n")
		elif self.integrator == "gslOdeIntegrator":
			fout.write("\t\t//! Interface for ODE \n")
			fout.write("\t\tvirtual void operator() (const baseType  x[], baseType  dydx[]);\n")
			fout.write("\t\t\n")
		else:
			raise Exception('unknown integrator')


		fout.write("\t\t//! Inlinefunktion fuer die NodeInfo\n")
		fout.write("\t\tvirtual const nodeInfo getNodeInfo() { nodeInfo n = {%s,_dynNode_,\"%s\" }; return n; }\n" % (self.nodeInfo, fileNameOut))
		fout.write("\t\t\n")

		fout.write("\t\t//! Reserviert Speicherplatz fuer die Nodeparameter\n")
		fout.write("\t\tstatic void registerStandardValues(); \n")
		fout.write("\t\t\n")

		fout.write("\t};\n")

		fout.write("}// Ende Namespace conedy\n")
		fout.write("\n")
		fout.write("#endif\n")

		fout.close()
		del fout
		
	def writeCppFile (self):

		#
		# .cpp schreiben
		#
		fileNameOut = self.nodeInfo[1:-1]
		fout = open("generated" + self.className + ".cpp", 'w')

		fout.write("#include \"generated%s.h\"" % self.className)
		fout.write("\n")
		fout.write("namespace conedy\n")
		fout.write("{\n")


		if len (self.events) > 0:
			fout.write("\t baseType %s::callBack ( unsigned int eventSignature) { \n" % self.className)
			counter = 0
			fout.write ("\t baseType nextEvent;\n ")
			for ev in self.events:
				fout.write("\t\t if (eventSignature == %i) { \n" % counter)
				fout.write(ev[1])
				fout.write("\t\t return nextEvent; \n")
				fout.write("\t\t } \n")
			fout.write("\t }\n")


			fout.write("\t %s::~%s (){ \n" % (self.className, self.className))
			fout.write("\t\t for (unsigned int i =0; i < numberOfEvents(); i++) eventHandler::unregisterCallBack(i); \n")
			fout.write("\t } \n")

			fout.write("\t %s::%s ( const %s &b) : %s (b), eventHandler (b) {\n" %(self.className, self.className, self.className, self.integrator))
			fout.write("\t\t for (unsigned int i =0; i < numberOfEvents(); i++) eventHandler::registerCallBack(i, time);} \n ")

		if (self.upkeep != ""):
			fout.write ("\t void %s::upkeep()" % self.className)
			fout.write ("\t{\n")
			fout.write(self.upkeep)
			fout.write ("\t}\n")


		dyn = self.dgl         #replace all parameter by the inline functions 
		for p in self.params:
			dyn = re.sub ("\\b" + p[0] + "\\b", p[0] + "()", dyn)

		self.dgl = dyn

		if self.integrator == "stdOdeIntegrator":
			fout.write("\t//! DGL von %s\n" % self.className)
			fout.write("\tvoid %s::operator()(const baseType x[], baseType dxdt[]) \n" % self.className)

			fout.write("\t{\n")
			fout.write(self.dgl)
			fout.write("\t}\n")
			fout.write("\n")
		elif self.integrator == "stdSdeIntegrator":
			fout.write("\t//! DGL von %s\n" % self.className)
			fout.write("\t void %s::operator()(baseType x[], baseType  dxdt[], baseType s[], baseType dsdx[]) \n" %self.className)	
			fout.write("\t{\n")
			fout.write(self.dgl)
			fout.write("\t}\n")
			fout.write("\n")
		elif self.integrator =="pcoBase":
			fout.write("\t//! phaseResponseCurve von %s\n" % self.className)
			fout.write("\tbaseType %s::phaseResponse(baseType coupling, baseType phase) \n" % self.className)
			fout.write("\t{\n")
			fout.write("\t baseType delta = 0;")
			fout.write(self.dgl)
			fout.write("\treturn delta;")
			fout.write("\t}\n")
			fout.write("\n")
		elif self.integrator =="pcoDelay":
			fout.write("\t//! phaseResponseCurve von %s\n" % self.className)
			fout.write("\tbaseType %s::phaseResponse(baseType coupling, baseType phase) \n" % self.className)
			fout.write("\t{\n")
			fout.write("\t baseType delta = 0;")
			fout.write(self.dgl)
			fout.write("\treturn delta;")
			fout.write("\t}\n")
			fout.write("\n")
		elif self.integrator =="mapNode":
			fout.write("\t//! Map von %s\n" % self.className)
			fout.write("\tvoid %s::operator()(baseType xprime[], baseType x[]) \n" % self.className)
			fout.write("\t{\n")
			fout.write(self.dgl)
			fout.write("\t}\n")
			fout.write("\n")
		elif self.integrator == "gslOdeIntegrator":
			fout.write("\t//! DGL von %s\n" % self.className)
			fout.write("\tvoid %s::operator()(const baseType x[], baseType dxdt[]) \n" % self.className)
			fout.write("\t{\n")
			fout.write(self.dgl)
			fout.write("\t}\n")
			fout.write("\n")
		else:
			raise Exception('unknown integrator')




		fout.write("\t//! Reserviert Speicherplatz fuer die %i Nodeparameter\n" % len(self.params) )
		fout.write("\tvoid %s::registerStandardValues() \n" % self.className)
		fout.write("\t{\n")
		i = 0

		
		if self.integrator =="pcoBase":
			fout.write("\t\tparams<baseType>::registerStandard( %s, \"%s_noiseFrequency\",0,params<baseType>::getStandardParameter (_pcoBase_, 0));\n" % (self.nodeInfo, fileNameOut))
			fout.write("\t\tparams<baseType>::registerStandard( %s, \"%s_noiseIntensity\",1,params<baseType>::getStandardParameter (_pcoBase_, 1));\n" % (self.nodeInfo, fileNameOut))
			i = 2
		
		if self.integrator =="pcoDelay":
			fout.write("\t\tparams<baseType>::registerStandard( %s, \"%s_noiseFrequency\",0,params<baseType>::getStandardParameter (_pcoBase_, 0));\n" % (self.nodeInfo, fileNameOut))
			fout.write("\t\tparams<baseType>::registerStandard( %s, \"%s_noiseIntensity\",1,params<baseType>::getStandardParameter (_pcoBase_, 1));\n" % (self.nodeInfo, fileNameOut))
			fout.write("\t\tparams<baseType>::registerStandard( %s, \"%s_timeDelay\",2,params<baseType>::getStandardParameter (_pcoDelay_, 2));\n" % (self.nodeInfo, fileNameOut))
			i = 3 

		for p in self.params:
			fout.write("\t\tparams<baseType>::registerStandard( %s, \"%s_%s\",%i,%f);\n" % (self.nodeInfo, fileNameOut, p[0], i, p[1]) )
			i += 1
		del i
		fout.write("\t}\n")
		fout.write("\t\n")

		fout.write("}\n\n")

		fout.close()
		del fout

		fout = open(".countAddedNodes" , 'w')
		fout.write(str(self.numberAddedNodes)+"\n")
		fout.close()


	def addNodeToNeurosim(self, fileNameOut=""):
	
		
		"Fuegt die Node in den Dateien generatedNodes.cpp, networkConstants.h, fullNetwork.h, Scanner.ll, Parser.yy, ... ein"

		if (fileNameOut == ""):
			fileNameOut = self.nodeInfo[1:-1]

		print "including " + fileNameOut


		#
		# generatedNodes.cpp
		#
		fout = open ("generatedNodes.cpp", 'a')
		fout.write	("#include \"generated%s.cpp\"\n" % self.className)
		fout.close()
		del fout

		#
		# neuroPython.cpp
		#

		fin = open("neuroPython.cpp", 'r')
		lines = fin.readlines()
		fin.close()
		del fin
		
		# "%{ 		// addNewNode.py Nodes
		start = 0
		for l in lines:
			if (l.find("addNewNode.py Nodes begin") >-1):
				break
			else:
				start += 1
		stop = start+1
		
		for l in lines[start+1:]:
			if (l.find("addNewNode.py Nodes end") >-1) :
				break
			else:
				stop +=1
		
		header = lines[:start+1]
		
		nodes = lines[start+1:stop]
		if self.static == 0:
			nodes.append("class_< nodeVirtualEdges<%s> , bases<nodeBlueprint> > (\"%s\",  reinterpret_cast<const char *>(__addedNodes_%s_%s) ); // added by addNewNodes.py \n" %(self.className, fileNameOut, self.integrator,self.className))
		elif self.static == 1:	
			self.staticEdgeType = self.staticEdgeType.replace ("_","<")
			hierachy = self.staticEdgeType.count ("<")
			self.staticEdgeType += ("<")
			self.staticEdgeType = self.staticEdgeType + (" edge")
			for i in range (0, hierachy):
				self.staticEdgeType += (">")
			

			nodes.append("class_< nodeTemplateEdges< %s >  , %s , %s >, bases<nodeBlueprint> > (\"%s\",  reinterpret_cast<const char *>(__addedNodes_%s_%s) ); // added by addNewNodes.py \n" %(self.staticEdgeType, self.staticTargetNodeType,self.className,  fileNameOut, self.integrator, self.className))
		nodes.sort()
	
		

		try:
			nodes.remove("\n")
		except:
			pass

		footer = lines[stop:]



		# neuroPython.cpp schreiben
		fout = open("neuroPython.cpp", 'w')
		fout.writelines(header)
		fout.writelines(nodes)
		fout.writelines(footer)
		fout.close()
		del fout, header, nodes, footer



		#
		# generatedRegisterStandards.h
		#
		fout = open ("generatedRegisterStandards.h", 'a')
		fout.write("%s::registerStandardValues();\n" % self.className)
		fout.close()
		del fout

		#
		# write documentation
		#

		fout = open("testing/addedNodes/" + self.integrator + "/"  + self.className + ".rst", 'w')




		
#		fout.write(self.className +"\n")
#		fout.write("------------------------------------------\n\n")

		for d in self.doku:
			fout.write(d)

		fout.write("\n\nDGL of %s\n" % self.className)
		fout.write("------------------------------------------\n\n")

		if (self.integrator == "pcoBase" or self.integrator == "pcoDelay"):
			fout.write("::\n")
			fout.write(self.dgl.replace("\n","\n\n\t"))
		else:		

#write documentation in math modus ???			
#			fout.write(".. math::\n\t")
#			fout.write(self.dgl.lstrip().replace("\n","\\\\\n\t"))#. replace("=","&="))

			fout.write("::\n")
			fout.write(self.dgl.replace("\n","\n\n\t"))



		fout.write ("\n\n")
	
		fout.write("Parameter of %s\n" % self.className)
		fout.write("-----------------------------------------\n\n")


		fout.write ("\n\n")

		for p in self.params:
			fout.write("- %s_%s \t\t =  %f; \n" % (self.className, p[0], p[1]) )

		fout.write("\n")

		fout = open("testing/addedNodes/" + self.integrator +"/" + self.className + ".py", 'w')
		fout.write("import conedy as ns\n\n")
		fout.write("net = ns.network()\n\n")
		fout.write("net.addNode(ns.%s())" % fileNameOut)
		fout.close()


		#
		#	generatedFullNetwork.h bearbeiten
		#
		fout = open("generatedFullNetwork.h", 'a')
		fout.write("#include \"generated%s.h\"\n" % self.className)
		fout.close()
		del fout
	
		#
		#	generatedAddNewNodes.yy
		#

		fout = open("generatedAddNewNode.yy", 'a')
		if (self.static == 0):
			fout.write("\t\t| %s { nodeBlueprint *n = new nodeVirtualEdges< %s >(); $$ = new constantCommand<nodeBlueprint*>(n); }\n" % (self.className.upper(), self.className))
		if (self.static ==1):
			fout.write("\t\t| %s { nodeBlueprint *n = new nodeTemplateEdges< %s  >    , %s , %s >(); $$ = new constantCommand<nodeBlueprint*>(n); }\n" % (self.className.upper(), self.staticEdgeType, self.staticTargetNodeType, self.className))
		fout.close()
		del fout





		#
		#	generatedAddNewNodesTokens.yy
		#

		fout = open("generatedAddNewNodeTokens.yy", 'a')
		fout.write("%token " + self.className.upper() + "\n")
		fout.close()
		del fout




		#
		# Scanner.ll
		#
		fin = open("Scanner.ll", 'r')
		lines = fin.readlines()
		fin.close()
		del fin
		
		# "%{ 		// addNewNode.py Nodes
		start = 0
		for l in lines:
			if (l.find("addNewNode.py Nodes") >-1):
				break
			else:
				start += 1
		stop = start+1
		
		for l in lines[start+1:]:
			if (l.find("%}") >-1) :
				break
			else:
				stop +=1
		
		header = lines[:start+2]
		

		nodes = lines[start+2:stop]
		nodes.append("%s\t\t\t{ return(ParserBase::%s); }  // added by addNewNodes.py  \n" % (fileNameOut, self.className.upper()))
		nodes.sort()
		
			

		try:
			nodes.remove("\n")
		except:
			pass

		footer = lines[stop+1:]

		# Scanner.ll schreiben
		fout = open("Scanner.ll", 'w')
		fout.writelines(header)
		fout.writelines(nodes)
		fout.writelines(footer)
		fout.close()
		del fout, header, nodes, footer




# MAINFUNCTION


if (len(sys.argv) < 2):
	print "give filename with node-description as argument."
	exit()


else:

	config = ConfigParser.RawConfigParser()
	config.read(sys.argv[1])
	
	for className in config.sections():


	
		n= NodeEditor()
		n.params = []
		n.events = []
		n.dgl = []

		try:
			numberEvents = config.getint(className, 'events')
			for i in  range (1,numberEvents+1 ):
				n.events.append( (i, config.get(className, 'event' + str(i))))
		except:
			n.events = []


		for i in  range (1,config.getint(className, 'parameter')+ 1):
			n.params.append( (config.get(className, 'parametername' + str(i)) , config.getfloat(className, 'standardvalue' + str(i))) )
		
		try:
				n.static = config.getboolean(className, 'staticEdges')
				n.staticEdgeType = config.get(className, 'staticEdgeType')
				n.staticTargetNodeType = config.get(className, 'staticTargetNodeType')
				
		except:
				n.static = 0
				n.staticEdgeType = ""
				n.staticTargetNodeType = ""

		n.className = className		
		n.nodeInfo  = "_" + n.className + "_" 
		n.dim = config.getint(className, 'dimension')
		n.parameter = config.getint(className, 'parameter')
		n.integrator = config.get(className, 'integrator')



		n.dgl = config.get(className, 'dynamics')
		

		try:
			n.documentation = config.get(className, 'dokumentation')
		except:
			n.documentation = []
		n.nodeInfo  = "_" + n.className + "_" 
		
		try:
			n.upkeep = config.get(className, 'upkeep')
		except:
			n.upkeep = ""


					
		n.writeHeaderFile()
		n.writeCppFile()
		n.addNodeToNeurosim()
		del (n)
