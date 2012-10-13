#!/bin/bash

(echo "setRandomSeed(0);";cat $*) | conedy  > output/$*.out 2> output/$*.err || true
sed -i "/#/d" output/$*.out
sum output/$** > results/sum_$* 
if [ -e "expected/sum_$*" ]; then 
	if [ "`diff expected/sum_$* results/sum_$*`" = "" ]; then 
		echo "test `pwd`/$* succeded"; 
	else echo "test `pwd`/$* failed !"; diff expected/sum_$* results/sum_$*;  
		echo "standard out of $*:" ; cat output/$*.out | sed "s/^/\t/g"; 
		echo "standard error of $*:" ; cat output/$*.err| sed "s/^/\t/g"; 
	fi 
else 
	echo "warning checksum for $* not present !"; 
fi
