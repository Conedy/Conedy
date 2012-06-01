
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


# generate a c-header with docstrings for all functions of the python interpreter. The docstring is in testing/*/<functionName>.rst
docstrings.h: addedNodes.sum.old
	rm -f docstrings.h
	touch docstrings.h
	cd testing; find -maxdepth 3 -name "*.rst" -exec sh -c  \
		'foo={}; (cat {}; echo -e "Example:\n--------\n"; sed "s/^/  /g" $${foo%.rst}.py) > $${foo%.rst};   #cat rst-file and  py file together \
		xxd -i  $${foo%.rst} >> ../docstrings.h; rm $${foo%.rst}' \;


#Generate the bisonc++ Parser file. Tokens are
Parser.yy: Parser.yy.tokens Parser.yy.declaration generatedAddNewNodeTokens.yy generatedAddNewNode.yy
	cat Parser.yy.tokens generatedAddNewNodeTokens.yy Parser.yy.declaration generatedAddNewNode.yy > Parser.yy
	echo ";" >> Parser.yy
	bisonc++ Parser.yy


Scanner.ll: Scanner.ll.begin Scanner.ll.end Scanner.ll.generated Parser.yy
	cat Scanner.ll.begin Scanner.ll.generated Scanner.ll.end > Scanner.ll

# generate sourcecode for node dynamics according to configuration files in addedNodes/ or in a special monitored directory configured in the config file (${addedDir}).
addNodes: addSharedNodes
	[ -d ${addedDir} ] && find -L ${addedDir} -maxdepth 1  -name "*.cfg" -type f -exec  sh -c "python addNewNode.py  {} || touch someNodeFailed"  \; || true
	[ ! -f someNodeFailed ]
	[ -d ${addedDir} ] && [ "$$(ls -A ${addedDir})/*.cfg" ] && (find ${addedDir} -maxdepth 1 -name "*.cfg" | sort | xargs sum >> addedNodes.sum.old) || true  ; \
	([ -d documentation ] && cp addedNodes.sum.old documentation/addedNodes.sum) || true


# generate sourcecode for node dynamics according to configuration files in addedNodes only.
addSharedNodes: revert
	rm -f someNodeFailed
	find -L addedNodes -maxdepth 1 -name "*.cfg" -type f -exec sh -c "python addNewNode.py {}  || touch someNodeFailed"  \;
	[ ! -f someNodeFailed ]
	sum addedNodes/*.cfg > addedNodes.sum.old;
	([ -d documentation ] && cp addedNodes.sum.old documentation/addedNodes.sum) || true


# Test if sourcecode for nodes specified in addedNodes/ needs to be created and call addSharedNodes if so. A list of already added nodes is maintained in addedNodes.sum.old
addSharedNodesIfNecessary:
	sum addedNodes/*.cfg > addedNodes.sum   || true
	[ ! -f addedNodes.sum.old ] && touch addedNodes.sum.old; \
	diff addedNodes.sum addedNodes.sum.old; \
	if [ $$? -eq 1 ]; then make addSharedNodes; fi



# check if new node configuration files have been added and call of addNodes if necessary. A list of already added nodes is maintained in addedNodes.sum.old
generatedAddNewNodeTokens.yy generatedAddNewNode.yy addedNodes.sum.old addNodesIfNecessary:
	sum addedNodes/*.cfg > addedNodes.sum; sum  ${addedDir}/*.cfg >> addedNodes.sum || true
	[ ! -f addedNodes.sum.old ] && touch addedNodes.sum.old; \
	diff addedNodes.sum addedNodes.sum.old; \
	if [ $$? -eq 1 ]; then make addNodes; fi

# remove all added Nodes
revert:
	rm -f generated*
	rm -f Scanner.ll.generated
	rm -f testing/addedNodes/*/*.rst
	rm -f testing/addedNodes/*/*.py
	rm -f testing/addedNodes/*/*.co
	rm -f testing/addedNodes/*/expected/*
	rm -f addedNodes.sum.old .countAddedNodes
	touch Scanner.ll.generated generatedNodes.cpp generatedFullNetwork.h generatedAddNewNodeTokens.yy generatedAddNewNode.yy generatedRegisterStandards.h generatedNeuroPython.cpp
#	touch Parser.yy	# tricking bjam  to call bisonc++ again after change of generatedAddNewNode.yy



# Create a hexadecimal representation of the users configuration file and sore it in string_config.h
string_config.h: config.h
	xxd -i config.h > string_config.h
	sed "/dirInstallRoot/d" config.h | grep dirInstall  | sed "s/dirInstall//g;s/=//g"  > dirInstall.h
	xxd -i dirInstall.h >> string_config.h






documentation:											# compile the documentation
	make -C documentation


documentation.install:


#doc:
#	doxygen

python-conedy.test:														# call all test-scripts in the testing directory and display failed scripts and scripts for which no checksum is present.
	cd testing; sh -c "make -s testPython-Conedy > ../testResult.python-conedy 2> ../testResult.python-conedy "
	cat testResult.python-conedy
	grep present testResult.python-conedy || true
	! grep failed testResult.python-conedy

conedy.test:
	cd testing;  sh -c " make -s testConedy > ../testResult.conedy 2> ../testResult.conedy"
	cat testResult.conedy
	! grep present testResult.conedy || true
	! grep failed testResult.conedy


conedy-src.test:   # if the testfile was already added, remove it and recompile first
	[ -f "${dirSrc}/addedNodes/testNode1.cfg" ] && ( ${noUserSpace} rm ${dirSrc}/addedNodes/testNode1.cfg &&\
		recompileConedy &&\
		recompilePython-Conedy) || true
	${noUserSpace} cp testNode1.cfg ${dirSrc}/addedNodes
	recompileConedy
	recompilePython-Conedy
	cd ${dirSrc}/testing/addedNodes/ode;  ${noUserSpace} sh -c 'make -s test_./testNode1.co > testResult.conedy-src 2> testResult.conedy-src'
	cd ${dirSrc}/testing/addedNodes/ode && ! grep failed testResult.conedy-src
	cd ${dirSrc}/testing/addedNodes/ode;  ${noUserSpace} sh -c 'make -s test_./testNode1.py > testResult.conedy-src 2> testResult.conedy-src'
	cd ${dirSrc}/testing/addedNodes/ode && ! grep failed testResult.conedy-src
	grep succeded ${dirSrc}/testing/addedNodes/ode/testResult.conedy-src
#	${noUserSpace} rm ${dirSrc}/addedNodes/testNode1.cfg
#	recompileConedy
#	recompilePython-Conedy


# Generate an conedy-executable called conedy_unstripped, which has optimization and debug symbols for profiling
unstripped: clean addNodes Scanner.ll Parser.yy
	bjam  conedy -o unstripped.sh
	tail -n2 unstripped.sh | sed "s/,--strip-all//" | sed "s/conedy/conedy_unstripped/" > linkUnstripped.sh
	make conedy
	bash linkUnstripped.sh


# build the bison-flex-interpreter of Conedy.
conedy: addNodesIfNecessary Parser.yy Scanner.ll string_config.h
	bjam  conedy cflags=-D$(SVNDEV) $(addprefix cflags=-D,${defines})  cflags=-D"ARCHITECTURE=linux64"  -j${numberCores}

installAndTest: install test


conedy.install: conedy
	mkdir -p ${dirInstall}
	find  bin -name "conedy" -exec cp -fa {} ${dirInstall}/conedy   \;
	cp -a recompileConedy ${dirInstall}
	sed -i "s+/etc/conedy.config+${globalConfig}+g"   ${dirInstall}/recompileConedy

conedy-root: addSharedNodesIfNecessary Parser.yy Scanner.ll string_config.h
	bjam  conedy cflags=-D$(SVNDEV) $(addprefix cflags=-D,${defines})  cflags=-D"ARCHITECTURE=linux64"  -j${numberCores}


conedy-root.install:
	mkdir -p ${dirInstallRoot}
	find  bin -name "conedy" -exec cp -fa {} ${dirInstallRoot}/conedy   \;
	cp -a recompileConedy ${dirInstallRoot}
	sed -i "s+/etc/conedy.config+${globalConfig}+g"   ${dirInstallRoot}/recompileConedy


conedy-root.uninstall:
	rm -f ${dirInstallRoot}/conedy
	rm -f ${dirInstallRoot}/recompileConedy
	rm -f ${dirInstallRoot}/recompilePython-Conedy



conedy.uninstall:
	rm -f ${dirInstall}/conedy
	rm -f ${dirInstall}/recompileConedy
	rm -f ${dirInstall}/recompilePython-Conedy

#	sed "s#DIRSRC#${dirSrc}#g" recompileNeurosimIfNecessary.sh | sed "s#ADDEDDIR#${addedDir}#g" > ${dirInstall}/recompileNeurosimIfNecessary.sh
#	chmod +x  ${dirInstall}/recompileNeurosimIfNecessary.sh


python-conedy: addNodesIfNecessary docstrings.h string_config.h # build the python bindings of Conedy.
	CFLAGS="-D$(SVNDEV) -DPYTHON $(addprefix -D,${defines})" python setup.py build


python-conedy.install: python-conedy
	python setup.py install --user
	cp -a recompilePython-Conedy ${dirInstall}
	sed -i "s+etc/conedy.config+${globalConfig}+g"   ${dirInstall}/recompilePython-Conedy


python-conedy-root: addSharedNodesIfNecessary string_config.h
	CFLAGS="-D$(SVNDEV) -DPYTHON $(addprefix -D,${defines})" python setup.py build


python-conedy-root.install:
	mkdir -p ${dirInstallRoot}
	python setup.py install
	cp -a recompilePython-Conedy ${dirInstallRoot}
	sed -i "s+etc/conedy.config+${globalConfig}+g"   ${dirInstallRoot}/recompilePython-Conedy


python-conedy-root.uninstall:
	rm -f ${dirInstallRoot}/recompilePython-conedy
	echo "Distutils does not support uninstalling. Please uninstall python-conedy manually."


python-conedy.uninstall:
	rm -f ${dirInstall}/recompilePython-conedy
	echo "Distutils does not support uninstalling. Please uninstall python-conedy manually."

conedy-src:
#	cp testNode.cfg ${dirSrc} addedNodes


conedy-src.install:
	mkdir -p ${dirSrc}
	cp `cat fileList`   ${dirSrc}/
	cp generated* ${dirSrc}/
	cp -r addedNodes ${dirSrc}/
	mkdir -p ${DESTDIR}/${dir ${globalConfig}}
	cp config.h ${DESTDIR}/${globalConfig}
#	ln -sf ${globalConfig} ${dirSrc}/config.h
	make -C testing clean
	cp -r testing ${dirSrc}/
	sed -i "s/^VERSION.*$$/VERSION = '${VERSION}'/" ${DESTDIR}/${globalConfig}
	sed -i "s#^include config.h#include \$${HOME}/.config/conedy/config.h#g" ${dirSrc}/Makefile



doc:
	doxygen


conedy-src.uninstall:
	rm -fr ${dirSrc}
#	rm -fr ${globalConfig}
#	cp -r testing ${dirSrc}/

python-conedy.recompile:
	${noUserSpace} HOME=${HOME} make docstrings.h addNodesIfNecessary string_config.h
ifdef pythonBjam
	([ -d build ] && ${noUserSpace} HOME=${HOME} bjam  python-conedy  cflags=-D$(SVNDEV) $(addprefix cflags=-D,${defines}) cflags=-D"ARCHITECTURE=linux64"  -j${numberCores} &&\
			${noUserSpace} cp -f bin/gcc*/release/python-conedy.so build/lib*/conedy.so ) \
		|| ( ${noUserSpace} make python-conedy python-conedy.install)
endif
	${noUserSpace} HOME=${HOME} make python-conedy.install
	${noUserSpace} rm recompilationPython-ConedyStarted


CONEDYSRC = $(addprefix ${dirSrc}/, $(shell cat fileList) )


copySrc:
	mkdir -p $(buildDir)
	ln -s $(CONEDYSRC) $(buildDir)  || true
	ln -s ${dirSrc}/addedNodes $(buildDir) || true
	cp -r ${dirSrc}/testing $(buildDir) || true


conedy.recompile:
	${noUserSpace} HOME=${HOME} make conedy conedy.install
	${noUserSpace} rm recompilationConedyStarted

clean: ${todo:=.clean}
	make revert

conedy.clean:
	rm -rf bin
	rm -rf Parserbase.h
	rm -f Scanner.ll
	rm -f string_config.h
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




win: string_config.h
	bjam toolset=gcc-ming target-os=windows conedy  cflags=-D"ARCHITECTURE=win32" -j${numberCores}

documentation.uninstall:

debug: addNodesIfNecessary Scanner.ll Parser.yy string_config.h
#	bisonc++ Parser.yy
	bjam conedyDebug cflags=-D$(SVNDEV) $(addprefix cflags=-D,${defines})  cflags=-D"ARCHITECTURE=linux64"  -j${numberCores}


debug.install: debug
	cp -f bin/gcc*/debug/conedyDebug ${dirInstall}
#	cp -f bin/gcc*/debug/conedyDebug  ${HOME}/bin/conedyDebug

debug.clean:

condor.install: conedy condor
	cp -f bin/gcc-*/debug/link-static/conedyCondor  ${dirInstall}
	cp -f bin/gcc-*/release/link-static/conedy ${dirInstall}/conedy.LINUX.X86_64.EXE
#	cp -f linux32/bin/gcc-mingw-4*/release/link-static/conedy ~/bin/conedy.LINUX.INTEL.EXE
#	cp -f bin/gcc-mingw-ming/release/link-static/target-os-windows/conedy ~/bin/conedy.WINNT51.INTEL.EXE
#	cp -f bin/gcc-mingw-ming/release/link-static/target-os-windows/conedy ~/bin/conedy.WINNT61.INTEL.EXE
#	cp -f bin/gcc-mingw-ming/release/link-static/target-os-windows/conedy ~/bin/conedy.WINNT60.INTEL.EXE

condor.clean:


condor: addNodesIfNecessary string_config.h               # build an interpreter which does not execute network-functions, but creates Condor-scripts which distribute the execution of loops (see vectorFor)
	bjam  conedyCondor cflags=-D$(SVNDEV) $(addprefix cflags=-D,${defines})  cflags=-D"ARCHITECTURE=linux64"  -j${numberCores}



SVNDEV="SVN_REV=$(VERSION)"

