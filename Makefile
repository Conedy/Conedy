
include config.h    # include the config file, which contains install directories. 




ARCH=$(shell dpkg --print-architecture)

ifeq ($(ARCH),amd64)
	BJAMARCH = "x86_64"
else
	BJAMARCH = "x86"
endif


build: ${todo}

config.h:
	./configure.sh



install: all ${todo:=.install}

uninstall: ${todo:=.uninstall}


test: ${todo:=.test}



docstrings.h: addedNodes.sum.old    			# generate a c-header with docstrings for all functions of the python interpreter. The docstring is in testing/*/<functionName>.rst
	rm -f docstrings.h 
	touch docstrings.h
	cd testing; find -maxdepth 3 -name "*.rst" -exec sh -c  \
		'foo={}; (cat {}; echo -e "Example:\n--------\n"; sed "s/^/  /g" $${foo%.rst}.py) > $${foo%.rst};   #cat rst-file and  py file together \
		xxd -i  $${foo%.rst} >> ../docstrings.h; rm $${foo%.rst}' \;




Scanner.ll: Scanner.ll.begin Scanner.ll.end Scanner.ll.generated
	cat Scanner.ll.begin Scanner.ll.generated Scanner.ll.end > Scanner.ll


addNodes: revert										# generate sourcecode for node dynamics according to configuration files in addedNodes/ or in a special monitored directory configured in the config file (${addedDir})
	rm -f someNodeFailed
	find -L addedNodes -maxdepth 1 -name "*.cfg" -type f -exec sh -c "python addNewNode.py {}  || touch someNodeFailed"  \;
	[ -d ${addedDir} ] && find -L ${addedDir} -maxdepth 1  -name "*.cfg" -type f -exec  sh -c "python addNewNode.py  {} || touch someNodeFailed"  \; || true
	[ ! -f someNodeFailed ]
	sum addedNodes/*.cfg > addedNodes.sum.old; 	
	[ -d ${addedDir} ] && [ "$$(ls -A ${addedDir})/*.cfg" ] && (find ${addedDir} -maxdepth 1 -name "*.cfg" | sort | xargs sum >> addedNodes.sum.old) || true  ; \
	
	
	
	([ -d documentation ] && cp addedNodes.sum.old documentation/addedNodes.sum) || true
	bisonc++ Parser.yy

addedNodes.sum.old addNodesIfNecessary:		# check if new node configuration files have been added and call addNodes if necessary. A list of already added nodes is maintained in addedNodes.sum.old
	sum addedNodes/*.cfg > addedNodes.sum; sum  ${addedDir}/*.cfg >> addedNodes.sum || true
	[ ! -f addedNodes.sum.old ] && touch addedNodes.sum.old; \
	diff addedNodes.sum addedNodes.sum.old; \
	if [ $$? -eq 1 ]; then make addNodes; fi

	
revert:													# remove all added Nodes  
	rm -f generated*
	rm -f Scanner.ll.generated
	rm -f testing/addedNodes/*/*.rst
	rm -f testing/addedNodes/*/*.py
	rm -f testing/addedNodes/*/*.co
	rm -f testing/addedNodes/*/expected/*
	rm -f addedNodes.sum.old .countAddedNodes
	touch Parser.yy	# tricking bjam to call bisonc++ again after change of generatedAddNewNode.yy


version:
SVNDEV="SVN_REV=$(VERSION)"


documentation:											# compile the documentation
	make -C documentation


documentation.install:


#doc:
#	doxygen

python-conedy.test:														# call all test-scripts in the testing directory and display failed scripts and scripts for which no checksum is present.
	cd testing; ${noUserSpace} sh -c "make -s testPython-Conedy > ../testResult.python-conedy 2> ../testResult.python-conedy "
	cat testResult.python-conedy
	grep present testResult.python-conedy || true 
	! grep failed testResult.python-conedy

conedy.test:
	cd testing; ${noUserSpace} sh -c " make -s testConedy > ../testResult.conedy 2> ../testResult.conedy"
	cat testResult.conedy
	! grep present testResult.conedy || true
	! grep failed testResult.conedy


conedy-src.test:   # if the testfile was already added, remove it and recompile first
	[ -f "${dirsrc}/addedNodes/testNode1.cfg" ] && ( ${noUserSpace} rm ${dirsrc}/addedNodes/testNode1.cfg &&\
		recompileConedy &&\
		recompilePython-Conedy) || true
	${noUserSpace} cp testNode1.cfg ${dirsrc}/addedNodes
	recompileConedy
	recompilePython-Conedy
	cd ${dirsrc}/testing/addedNodes/ode;  ${noUserSpace} sh -c 'make -s test_./testNode1.co > testResult.conedy-src 2> testResult.conedy-src'
	cd ${dirsrc}/testing/addedNodes/ode && ! grep failed testResult.conedy-src
	cd ${dirsrc}/testing/addedNodes/ode;  ${noUserSpace} sh -c 'make -s test_./testNode1.py > testResult.conedy-src 2> testResult.conedy-src'
	cd ${dirsrc}/testing/addedNodes/ode && ! grep failed testResult.conedy-src
	grep succeded ${dirsrc}/testing/addedNodes/ode/testResult.conedy-src
#	${noUserSpace} rm ${dirsrc}/addedNodes/testNode1.cfg
#	recompileConedy
#	recompilePython-Conedy



unstripped: clean addNodes
	bjam conedy -o unstripped.sh
	tail -n2 unstripped.sh | sed "s/,--strip-all//" | sed "s/conedy/conedy_unstripped/" > linkUnstripped.sh
	make conedy	
	bash linkUnstripped.sh	



conedy: addNodesIfNecessary Scanner.ll version				# build the bison-flex-interpreter of Conedy.
	bjam conedy cflags=-D$(SVNDEV) $(addprefix cflags=-D,${defines})  cflags=-D"ARCHITECTURE=linux64"  -j${numberCores}

installAndTest: install test


conedy.install: conedy
	mkdir -p ${dirinstall}
	find bin -name "conedy" -exec cp -f {} ${dirinstall}/conedy   \;
	cp -a recompileConedy ${dirinstall}
	sed -i "s+/etc/conedy.config+${globalConfig}+g"   ${dirinstall}/recompileConedy 

conedy.uninstall:
	rm -f ${dirinstall}/conedy
	rm -f ${dirinstall}/recompileConedy

#	sed "s#DIRSRC#${dirsrc}#g" recompileNeurosimIfNecessary.sh | sed "s#ADDEDDIR#${addedDir}#g" > ${dirinstall}/recompileNeurosimIfNecessary.sh
#	chmod +x  ${dirinstall}/recompileNeurosimIfNecessary.sh


python-conedy: addNodesIfNecessary docstrings.h # build the python bindings of Conedy.


	
	CFLAGS=-D$(SVNDEV) python setup.py build


python-conedy.install: python-conedy
	python setup.py install
	cp -a recompilePython-Conedy ${dirinstall}
	sed -i "s+etc/conedy.config+${globalConfig}+g"   ${dirinstall}/recompilePython-Conedy 

python-conedy.uninstall:
	rm -f ${dirinstall}/recompilePython-conedy
	echo "Distutils does not support uninstalling. Please uninstall python-conedy manually."

conedy-src:
#	cp testNode.cfg ${dirsrc} addedNodes


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
	${noUserSpace} HOME=${HOME} make docstrings.h addNodesIfNecessary version
#	([ -d build ] && ${noUserSpace} HOME=${HOME} bjam python-conedy cflags=-D$(SVNDEV) cflags=-D"ARCHITECTURE=linux64"  -j${numberCores} &&\
			${noUserSpace} cp -f bin/gcc*/release/python-conedy.so build/lib*/conedy.so ) \
		|| ( ${noUserSpace} make python-conedy python-conedy.install)
	${noUserSpace} HOME=${HOME} make python-conedy.install
	${noUserSpace} rm recompilationPython-ConedyStarted




conedy.recompile: 
	${noUserSpace} HOME=${HOME} make conedy conedy.install
	${noUserSpace} rm recompilationConedyStarted
	
clean: ${todo:=.clean}
	make revert

conedy.clean:
	rm -rf bin
	rm -rf Parserbase.h
	rm -f Scanner.ll
	make revert

python-conedy.clean:
	python setup.py clean
	rm -rf build
	rm -f docstrings.h

documentation.clean:
	make -C documentation clean

conedy-src.clean:



.PHONY: documentation addNodesIfNecessary conedy.install uninstall conedy.uninstall python-conedy.uninstall conedy-src.uninstall install python-conedy python-conedy.install conedy-src.install  all opt debug opengl win linux32 condor benchmark icc revert addNodes 


.SILENT: config.h

##unofficial




win: version
	bjam toolset=gcc-ming target-os=windows conedy  cflags=-D"ARCHITECTURE=win32" -j${numberCores}

documentation.uninstall:

debug: addNodesIfNecessary Scanner.ll version
#	bisonc++ Parser.yy
	bjam conedyDebug cflags=-D$(SVNDEV) $(addprefix cflags=-D,${defines})  cflags=-D"ARCHITECTURE=linux64"  -j${numberCores}


debug.install: debug
#	cp -f bin/gcc*/debug/conedyDebug ${dirinstall} 
	cp -f bin/gcc*/debug/conedyDebug /home/alex/bin/conedyDebug

debug.clean:

condor.install:
	cp -f bin/gcc-*/debug/link-static/conedyCondor ${dirinstall}

condor.clean:


condor: addNodesIfNecessary version               # build an interpreter which does not execute network-functions, but creates Condor-scripts which distribute the execution of loops (see vectorFor)
	bjam conedyCondor cflags=-D$(SVNDEV) $(addprefix cflags=-D,${defines})  cflags=-D"ARCHITECTURE=linux64"  -j${numberCores}


installCondor: 
	cp -f bin/gcc-*/release/link-static/conedy ~/bin/conedy.LINUX.X86_64.EXE
#	cp -f linux32/bin/gcc-mingw-4*/release/link-static/conedy ~/bin/conedy.LINUX.INTEL.EXE
#	cp -f bin/gcc-mingw-ming/release/link-static/target-os-windows/conedy ~/bin/conedy.WINNT51.INTEL.EXE
#	cp -f bin/gcc-mingw-ming/release/link-static/target-os-windows/conedy ~/bin/conedy.WINNT61.INTEL.EXE
#	cp -f bin/gcc-mingw-ming/release/link-static/target-os-windows/conedy ~/bin/conedy.WINNT60.INTEL.EXE


