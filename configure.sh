#!/usr/bin/make -sf



config.h: 
	echo "--------------------------------------------"
	echo "Conedy is not configured yet."
	echo "Copying config.h.tmpl -> config.h"
	sed "s#\$$HOME#${HOME}#g" config.h.tmpl > config.h
	echo "Please adjust the variables in config.h to your needs."
	echo "--------------------------------------------"
