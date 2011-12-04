#!/bin/bash

name=$1
name=${name%.rst}
name=${name#./}



(echo -n ".. _"; echo -n "${name}"   ; echo -en ":\n\n"; 
echo "\`\`${name}\`\`"; 
echo -e "=====================================================\n";  
cat $1;

echo -e "\n\nExample (python-conedy)\n-------\n::\n" ; 

sed "s/^/  /g" ${name}.py 

echo -e "\n\nExample (conedy)\n-------\n::\n" ; 
#echo -e ".. code-block:: c++";


sed "s/^/  /g" ${name}.co) 


