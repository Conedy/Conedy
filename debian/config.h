


# Please choose on of the following conedy python-conedy conedy-src

todo =  conedy conedy-src documentation



# Installation directory (with path)
# Example:
 dirinstall = ${DESTDIR}/usr/bin/

#dirinstall = CHANGEME

# Installation directory for specific files 
# Example:
 dirsrc = ${DESTDIR}/usr/share/conedy

#dirsrc = CHANGEME


# monitor directory for added nodes
# Example:
addedDir = ${HOME}/.config/conedy/addedNodes

#addedDir = CHANGEME


noUserSpace = sudo


globalConfig = /etc/conedy.config

#number of cores

numberCores = `cat /proc/cpuinfo | grep processor | wc -l`


VERSION = `head debian/changelog -n1 | awk '{print $$2}'  | sed "s/(//" | sed "s/)//" `

.SILENT:	all

