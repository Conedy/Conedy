# Makefile for Sphinx documentation
#

# You can set these variables from the command line.
SPHINXOPTS    =
SPHINXBUILD   = sphinx-build
PAPER         =
BUILDDIR      = _build

# Internal variables.
PAPEROPT_a4     = -D latex_paper_size=a4
PAPEROPT_letter = -D latex_paper_size=letter
ALLSPHINXOPTS   = -d $(BUILDDIR)/doctrees $(PAPEROPT_$(PAPER)) $(SPHINXOPTS) .

.PHONY: help clean html dirhtml pickle json htmlhelp qthelp latex changes linkcheck doctest getDocFromTesting reference.rst


all: html latex 	
	make -C _build/latex all-pdf
	


addedNodes.sum:
	make -C ../ addNodes


updateDocIfNecessary: addedNodes.sum
	[ ! -f addedNodes.sum.old ] && touch addedNodes.sum.old; \
	diff addedNodes.sum.old addedNodes.sum;\
	if [ $$? -eq 1 ]; then make getDocFromTesting; fi


getDocFromTesting:															# 
#	make -C ../ addNodes
	mkdir -p reference/nodes
	mkdir -p reference/network
	mkdir -p reference/network/create\ manipulate
	mkdir -p reference/network/observe\ dynamics
	mkdir -p reference/network/measures
	mkdir -p reference/nodes/mapNode
	mkdir -p reference/nodes/ode
	mkdir -p reference/nodes/sde
	mkdir -p reference/nodes/pco
	mkdir -p reference/nodes/pcoDelay
	mkdir -p reference/network/edges

	cd ../testing/createNetwork; find -name '*.rst' -execdir sh -c 'name={}; ../../documentation/mergeDocExample.sh {} > ../../documentation/reference/network/create\ manipulate/$${name#./}' \; 
	cd ../testing/statisticsNetwork; find -name '*.rst' -execdir sh -c 'name={}; ../../documentation/mergeDocExample.sh {} > ../../documentation/reference/network/measures/$${name#./}' \; 
	cd ../testing/dynNetwork; find -name '*.rst' -execdir sh -c 'name={}; ../../documentation/mergeDocExample.sh {} > ../../documentation/reference/network/observe\ dynamics/$${name#./}' \; 
	cd ../testing/network; find -name '*.rst' -execdir sh -c 'name={}; ../../documentation/mergeDocExample.sh {} > ../../documentation/reference/network/create\ manipulate/$${name#./}' \; 
	cd ../testing/edges; find -name '*.rst' -execdir sh -c 'name={}; ../../documentation/mergeDocExample.sh {} > ../../documentation/reference/network/edges/$${name#./}' \; 

	cd ../testing/global; find -name '*.rst' -execdir sh -c 'name={}; ../../documentation/mergeDocExample.sh {} > ../../documentation/reference/$${name#./}' \; 

#	cd ../testing/addedNodes; find -name '*.rst' -execdir sh -c 'name={}; ../../../documentation/mergeDocExample.sh {} > ../../../documentation/reference/nodes/$${name#./}' \; 
	cd ../testing/addedNodes/mapNode; find -name '*.rst' -execdir sh -c 'name={}; ../../../documentation/mergeDocExample.sh {} > ../../../documentation/reference/nodes/mapNode/$${name#./}' \; 
	cd ../testing/addedNodes/ode; find -name '*.rst' -execdir sh -c 'name={}; ../../../documentation/mergeDocExample.sh {} > ../../../documentation/reference/nodes/ode/$${name#./}' \; 
	cd ../testing/addedNodes/sde; find -name '*.rst' -execdir sh -c 'name={}; ../../../documentation/mergeDocExample.sh {} > ../../../documentation/reference/nodes/sde/$${name#./}' \; 
	cd ../testing/addedNodes/pco; find -name '*.rst' -execdir sh -c 'name={}; ../../../documentation/mergeDocExample.sh {} > ../../../documentation/reference/nodes/pco/$${name#./}' \; 
	cd ../testing/addedNodes/pcoDelay; find -name '*.rst' -execdir sh -c 'name={}; ../../../documentation/mergeDocExample.sh {} > ../../../documentation/reference/nodes/pcoDelay/$${name#./}' \; 


	cp network.tmpl reference/network.rst
	cp create\ manipulate.tmpl reference/network/create\ manipulate.rst
	cp observe\ dynamics.tmpl reference/network/observe\ dynamics.rst
	cp network\ measures.tmpl reference/network/measures.rst
	cp pco.tmpl reference/nodes/pco.rst
	cp pcoDelay.tmpl reference/nodes/pcoDelay.rst
	cp ode.tmpl reference/nodes/ode.rst
	cp sde.tmpl reference/nodes/sde.rst
	cp mapNode.tmpl reference/nodes/mapNode.rst
	cp nodes.tmpl reference/nodes.rst
	cp edges.tmpl reference/network/edges.rst
	cp random.tmpl reference/network/random.rst
	cp addedNodes.sum addedNodes.sum.old
	cp referenceHeader.tmpl reference.rst	


updateVersionNumber:
	cd ..; sed "s/^release.*$$/release = '${VERSION}'/" -i documentation/conf.py
	sed "s/RELEASELONG/${VERSIONLONG}/g" download.tmpl | sed "s/RELEASE/${VERSION}/g"  > download.rst

reference.rst: updateDocIfNecessary updateVersionNumber
#	cd reference;  ls | sed "s/\t/\n/g;s/.rst//g;s#^# /reference/#g" >> ../reference.rst

install: all
	mkdir -p $${DESTDIR}/documentation/html
	cp -r _build/html $${DESTDIR}/documentation/html
	cp  _build/latex/networkS.pdf $${DESTDIR}/documentation


help:
	@echo "Please use \`make <target>' where <target> is one of"
	@echo "  html      to make standalone HTML files"
	@echo "  dirhtml   to make HTML files named index.html in directories"
	@echo "  pickle    to make pickle files"
	@echo "  json      to make JSON files"
	@echo "  htmlhelp  to make HTML files and a HTML help project"
	@echo "  qthelp    to make HTML files and a qthelp project"
	@echo "  latex     to make LaTeX files, you can set PAPER=a4 or PAPER=letter"
	@echo "  changes   to make an overview of all changed/added/deprecated items"
	@echo "  linkcheck to check all external links for integrity"
	@echo "  doctest   to run all doctests embedded in the documentation (if enabled)"

clean:
	-rm -rf $(BUILDDIR)
	rm -rf reference
	rm -f addedNodes.sum.old

html: reference.rst
	mkdir -p _build/html
	$(SPHINXBUILD) -b html $(ALLSPHINXOPTS) $(BUILDDIR)/html
	@echo
	@echo "Build finished. The HTML pages are in $(BUILDDIR)/html."

dirhtml:
	$(SPHINXBUILD) -b dirhtml $(ALLSPHINXOPTS) $(BUILDDIR)/dirhtml
	@echo
	@echo "Build finished. The HTML pages are in $(BUILDDIR)/dirhtml."

pickle:
	$(SPHINXBUILD) -b pickle $(ALLSPHINXOPTS) $(BUILDDIR)/pickle
	@echo
	@echo "Build finished; now you can process the pickle files."

json:
	$(SPHINXBUILD) -b json $(ALLSPHINXOPTS) $(BUILDDIR)/json
	@echo
	@echo "Build finished; now you can process the JSON files."

htmlhelp:
	$(SPHINXBUILD) -b htmlhelp $(ALLSPHINXOPTS) $(BUILDDIR)/htmlhelp
	@echo
	@echo "Build finished; now you can run HTML Help Workshop with the" \
	      ".hhp project file in $(BUILDDIR)/htmlhelp."

qthelp:
	$(SPHINXBUILD) -b qthelp $(ALLSPHINXOPTS) $(BUILDDIR)/qthelp
	@echo
	@echo "Build finished; now you can run "qcollectiongenerator" with the" \
	      ".qhcp project file in $(BUILDDIR)/qthelp, like this:"
	@echo "# qcollectiongenerator $(BUILDDIR)/qthelp/networkS.qhcp"
	@echo "To view the help file:"
	@echo "# assistant -collectionFile $(BUILDDIR)/qthelp/networkS.qhc"

latex: reference.rst
	mkdir -p _build/latex
	$(SPHINXBUILD) -b latex $(ALLSPHINXOPTS) $(BUILDDIR)/latex
	@echo
	@echo "Build finished; the LaTeX files are in $(BUILDDIR)/latex."
	@echo "Run \`make all-pdf' or \`make all-ps' in that directory to" \
	      "run these through (pdf)latex."

changes:
	$(SPHINXBUILD) -b changes $(ALLSPHINXOPTS) $(BUILDDIR)/changes
	@echo
	@echo "The overview file is in $(BUILDDIR)/changes."

linkcheck:
	$(SPHINXBUILD) -b linkcheck $(ALLSPHINXOPTS) $(BUILDDIR)/linkcheck
	@echo
	@echo "Link check complete; look for any errors in the above output " \
	      "or in $(BUILDDIR)/linkcheck/output.txt."

doctest:
	$(SPHINXBUILD) -b doctest $(ALLSPHINXOPTS) $(BUILDDIR)/doctest
	@echo "Testing of doctests in the sources finished, look at the " \
	      "results in $(BUILDDIR)/doctest/output.txt."



include ../config.h
