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


#!/usr/bin/env python



#setup.py
from distutils.core import setup
from distutils.extension import Extension
import os.path
import sys


files = ["neuroPython.cpp",  "fullNetwork.cpp",  "nodeImplement.cpp", "generatedNodes.cpp",  "neuronModels.cpp","phaseResponseOscillators.cpp" , "sdeNode.cpp",  "cnnNode.cpp" , "stdSdeIntegrator.cpp", "stdOdeIntegrator.cpp", "gslOdeNode.cpp" ,"ioNode.cpp" ,"pulseCoupledPhaseOscillator.cpp","pulseCoupledExcitatoryNeuron.cpp" ,"network.cpp" ,"dynNetwork.cpp" ,"createNetwork.cpp", "spatialNetwork.cpp","mapNode.cpp" ,"eventHandler.cpp" ,"node.cpp" ,"edge.cpp" ,"dynNode.cpp" ,"gslNoise.cpp" ,"statisticsNetwork.cpp" ,"commandLineArguments.cpp" ]


if sys.platform == "win32" :
	include_dirs = ["C:\\Program Files (x86)\\boost\\boost_1_46_1"]
	libraries=["gsl", "cblas"]
	library_dirs=['C:\\Program Files (x86)\\boost\\boost_1_46_1\\lib']

	module = Extension("conedy",  files, library_dirs=library_dirs,
				libraries=libraries,
				include_dirs=include_dirs,
				depends=[])

	module.extra_compile_args = ['/GX']			

else :
	include_dirs = ["/usr/include/boost","."]
	libraries=["boost_python","gsl", "gslcblas", "boost_iostreams", "z"]
	library_dirs=['/usr//lib']


	module = Extension("conedy",  files, library_dirs=library_dirs,
				libraries=libraries,
				include_dirs=include_dirs,
				depends=[])



#files =["neuroPython.cpp","spatialNetwork.cpp"]



			

setup(name="conedy",  version="0.20",
		ext_modules=[module])
