

test: testConedy testPython-Conedy


testConedy:
	mkdir -p output
	mkdir -p expected
	mkdir -p results
	find  -maxdepth 1 -name '*.co' -exec make -s test_{} \;


testPython-Conedy:
	mkdir -p output
	mkdir -p expected
	mkdir -p results
	find  -maxdepth 1 -name '*.py' -exec make -s test_{} \;









test_./%.py:
	sed 's/import conedy as co/import conedy as co\nco.setRandomSeed(0)/' $*.py | python > output/$*.py.out 2> output/$*.py.err || true
	sed -i "/#/d" output/$*.py.out
	sum output/$*.py*  > results/sum_$*.py 
	if [ -e "expected/sum_$*.py" ]; then \
		if [ "`diff expected/sum_$*.py results/sum_$*.py`" = "" ]; then \
			echo "test `pwd`/$*.py succeded"; \
		else echo "test `pwd`/$*.py failed !"; diff expected/sum_$*.py results/sum_$*.py; \
		fi; \
	else echo "warning checksum for $*.py not present !"; \
	fi

test_./%.co:
	(echo "setRandomSeed(0);";cat $*.co) | conedy  > output/$*.co.out 2> output/$*.co.err || true
	sed -i "/#/d" output/$*.co.out
	sum output/$*.co* > results/sum_$*.co 
	if [ -e "expected/sum_$*.co" ]; then \
		if [ "`diff expected/sum_$*.co results/sum_$*.co`" = "" ]; then echo "test `pwd`/$*.co succeded"; else echo "test `pwd`/$*.co failed !"; diff expected/sum_$*.co results/sum_$*.co;  fi \
	else \
		echo "warning checksum for $*.co not present !"; \
	fi
		

confirm_./%.py:
	sed 's/import conedy as co/import conedy as co\nco.setRandomSeed(0)/' $*.py | python > output/$*.py.out 2> output/$*.py.err || true
	sed -i "/#/d" output/$*.py.out
	sum output/$*.py* >  expected/sum_$*.py
	
confirm_./%.co:
	(echo "setRandomSeed(0);";cat $*.co) | conedy  > output/$*.co.out 2> output/$*.co.err || true
	sed -i "/#/d" output/$*.co.out
	sum output/$*.co* >  expected/sum_$*.co





submit:
	cd expected; git add sum_template.py



clean:
	rm -rf output
	rm -rf results




.PHONY: test clean
