#!/bin/bash

~/bin/neuroDebug calcCNN.ns

/bin/sed -i 's/ /\n/g' output/results.txt

/usr/bin/vim output/results.txt RefData/out*199 -O
