


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



#addedDir = CHANGEME

# A directory which is monitored by Conedy for files which specify new nodes with user-added dynamics.

addedDir = ${HOME}/.config/conedy/addedNodes


#In case you install Conedy's sources and executables into a directory, which is not in userspace, recompilation will require root-priviledges. Choose the tool, which allows to acquire root-priviledges. sudo or kdesudo will work fine. For an installation in userspace noUserSpace can be left empty. 

noUserSpace = sudo


globalConfig = /etc/conedy.config

#number of cores

numberCores = `cat /proc/cpuinfo | grep processor | wc -l`


VERSIONLONG = `head debian/changelog -n1 | awk '{print $$2}'  | sed "s/(//" | sed "s/)//" `

VERSION= `head debian/changelog -n1 | awk '{print $$2}'  | sed "s/(//" | sed "s/)//" | sed "s/-.*//`


.SILENT:	all

