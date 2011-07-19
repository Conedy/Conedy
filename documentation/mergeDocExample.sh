#!/bin/bash

name=$1
name=${name%.rst}
name=${name#./}



(echo -n ".. _"; echo -n "${name} "   ; echo -en ":\n\n"; 
echo ${name}; 
echo -e "=====================================================\n";  
cat $1;

echo -e "\n\nExample\n-------\n::\n" ; 

sed "s/^/  /g" ${name}.py) 




