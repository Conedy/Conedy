

include config.h    # include the config file, which contains install directories. 




ARCH=$(shell dpkg --print-architecture)

ifeq ($(ARCH),amd64)
	BJAMARCH = "ia64"
else
	BJAMARCH = "x86"
endif


build: ${todo}

config.h:
	./configure.sh



install: all ${todo:=.install}

uninstall: ${todo:=.uninstall}

docstrings.h: addedNodes.sum.old    			# generate a c-header with docstrings for all functions of the python interpreter. The docstring is in testing/*/<functionName>.rst
	rm -f docstrings.h 
	touch docstrings.h
	cd testing; find -maxdepth 3 -name "*.rst" -exec sh -c  \
		'foo={}; (cat {}; echo -e "Example:\n--------\n"; sed "s/^/  /g" $${foo%.rst}.py) > $${foo%.rst};   #cat rst-file and  py file together \
		xxd -i  $${foo%.rst} >> ../docstrings.h; rm $${foo%.rst}' \;



addNodes: revert										# generate sourcecode for node dynamics according to configuration files in addedNodes/ or in a special monitored directory configured in the config file (${addedDir})
	find -L addedNodes -maxdepth 1 -name "*.cfg" -type f -exec python addNewNode.py {} \;
	find -L ${addedDir} -maxdepth 1  -name "*.cfg" -type f -exec python addNewNode.py {} \; || true
	sum addedNodes/*.cfg > addedNodes.sum.old; sum ${addedDir}/*.cfg  >> addedNodes.sum.old  || true
	[ -d documentation ] && cp addedNodes.sum.old documentation/addedNodes.sum
	bisonc++ Parser.yy

addedNodes.sum.old addNodesIfNecessary:		# check if new node configuration files have been added and call addNodes if necessary. A list of already added nodes is maintained in addedNodes.sum.old
	sum addedNodes/*.cfg > addedNodes.sum; sum  ${addedDir}/*.cfg >> addedNodes.sum || true
	[ ! -f addedNodes.sum.old ] && touch addedNodes.sum.old; \
	diff addedNodes.sum addedNodes.sum.old; \
	if [ $$? -eq 1 ]; then make addNodes; fi

	
revert:													# remove all added Nodes  
	rm -f generated*
	/usr/bin/env sed -i "/added by addNewNodes.py/d" Scanner.ll
	/usr/bin/env sed -i "/added by addNewNodes.py/d" neuroPython.cpp
	rm -f testing/addedNodes/*/*.rst
	rm -f testing/addedNodes/*/*.py
	rm -f addedNodes.sum.old .countAddedNodes
	touch Parser.yy	# tricking bjam to call bisonc++ again after change of generatedAddNewNode.yy


version:
SVNDEV="SVN_REV=$(VERSION)"


documentation:
	make -C documentation


documentation.install:


doc:
	doxygen

test:														# call all test-scripts in the testing directory and display failed scripts and scripts for which no checksum is present.
	make -C testing > testResult 2> testResult
	grep failed testResult
	grep present testResult


conedy: addNodesIfNecessary version				# build the bison-flex-interpreter of Conedy.
	bjam conedy cflags=-D$(SVNDEV) cflags=-D"ARCHITECTURE=linux64"  -j${numberCores}


conedy.install: conedy
	mkdir -p ${dirinstall}
	find bin -name "conedy" -exec cp {} ${dirinstall}/conedy   \;
	cp -a recompileConedy ${dirinstall}
	sed -i "s+/etc/conedy.config+${globalConfig}+g"   ${dirinstall}/recompileConedy 

conedy.uninstall:
	rm -f ${dirinstall}/conedy
	rm -f ${dirinstall}/recompileConedy

#	sed "s#DIRSRC#${dirsrc}#g" recompileNeurosimIfNecessary.sh | sed "s#ADDEDDIR#${addedDir}#g" > ${dirinstall}/recompileNeurosimIfNecessary.sh
#	chmod +x  ${dirinstall}/recompileNeurosimIfNecessary.sh


python-conedy:  docstrings.h addNodesIfNecessary version    # build the python bindings of Conedy.
	CFLAGS=-D$(SVNDEV) python setup.py build


python-conedy.install: python-conedy
	python setup.py install
	cp -a recompilePython-Conedy ${dirinstall}
	sed -i "s+etc/conedy.config+${globalConfig}+g"   ${dirinstall}/recompilePython-Conedy 

python-conedy.uninstall:
	rm -f ${dirinstall}/recompilePython-conedy
	echo "Distutils does not support uninstalling. Please uninstall python-conedy manually."

conedy-src:


conedy-src.install:
	mkdir -p ${dirsrc}
	cp `cat fileList`   ${dirsrc}/
	cp generated* ${dirsrc}/
	cp -r addedNodes ${dirsrc}/
	mkdir -p ${DESTDIR}/${dir ${globalConfig}}
	cp config.h ${DESTDIR}/${globalConfig}
#	ln -sf ${globalConfig} ${dirsrc}/config.h
	make -C testing clean
	cp -r testing ${dirsrc}/
	sed -i "s/^VERSION.*$$/VERSION = '${VERSION}'/" ${DESTDIR}/${globalConfig}
	sed -i "s#^include config.h#include \$${HOME}/.config/conedy/config.h#g" ${dirsrc}/Makefile

conedy-src.uninstall:
	rm -fr ${dirsrc}
#	rm -fr ${globalConfig}
#	cp -r testing ${dirsrc}/

python-conedy.recompile: 
	${noUserSpace} HOME=${HOME} make python-conedy python-conedy.install
	${noUserSpace} rm recompilationPython-ConedyStarted

	

conedy.recompile: 
	${noUserSpace} HOME=${HOME} make conedy conedy.install
	${noUserSpace} rm recompilationConedyStarted
	


clean:
	rm -rf bin
	python setup.py clean
	rm -rf build
	rm -f Parserbase.h docstrings.h
	make revert
	make -C documentation clean

.PHONY: documentation addNodesIfNecessary conedy.install uninstall conedy.uninstall python-conedy.uninstall conedy-src.uninstall install python-conedy python-conedy.install conedy-src.install  all opt debug opengl win linux32 condor benchmark icc revert addNodes


.SILENT: config.h

##unofficial




win: version
	bjam toolset=gcc-ming target-os=windows conedy  cflags=-D"ARCHITECTURE=win32" -j${numberCores}

documentation.uninstall:

debug: addNodesIfNecessary version
#	bisonc++ Parser.yy
	bjam conedyDebug  -j${numberCores}
	cp -f bin/gcc*/debug/conedyDebug ~/bin/conedyDebug

condor: addNodesIfNecessary version               # build an interpreter which does not execute network-functions, but creates Condor-scripts which distribute the execution of loops (see vectorFor)
	bjam conedyCondor -j${numberCores}
	cp -f bin/gcc-*/debug/link-static/conedyCondor ~/bin


installCondor: 
	cp -f bin/gcc-*/release/link-static/conedy ~/bin/conedy.LINUX.X86_64.EXE
#	cp -f linux32/bin/gcc-mingw-4*/release/link-static/conedy ~/bin/conedy.LINUX.INTEL.EXE
#	cp -f bin/gcc-mingw-ming/release/link-static/target-os-windows/conedy ~/bin/conedy.WINNT51.INTEL.EXE
#	cp -f bin/gcc-mingw-ming/release/link-static/target-os-windows/conedy ~/bin/conedy.WINNT61.INTEL.EXE
#	cp -f bin/gcc-mingw-ming/release/link-static/target-os-windows/conedy ~/bin/conedy.WINNT60.INTEL.EXE


