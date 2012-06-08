
# Specify, which parts of conedy should be build and installed. Please choose one of the following: conedy python-conedy conedy-src documentation condor

todo =  conedy-root conedy-src documentation


# Installation directory for the the conedy executable and the recompilation scripts. For convenience, choose a directory in your path.

dirInstall = ${HOME}/bin

# Installation directory for the source files of conedy. This allows other users to recompile conedy. 
dirSrc = ${DESTDIR}/usr/share/conedy


# Installation directory
dirInstallRoot = ${DESTDIR}/usr/bin

# monitor directory for added nodes   
addedDir = ${HOME}/.config/conedy/addedNodes






# Build directory. 
buildDir = ${HOME}/.config/conedy/build


#A place for the global config of conedy
globalConfig = /etc/conedy.config


#number of cores
numberCores = `cat /proc/cpuinfo | grep processor | wc -l`


#Compile the python extension with bjam, which is much faster as distutils has no real dependenccy resolution and does not use more than one cpu core. If pythonBjam is not defined at all, distutils will build the extension.
pythonBjam = true 


VERSIONLONG = `head debian/changelog -n1 | awk '{print $$2}'  | sed "s/(//" | sed "s/)//" `

VERSION= `head debian/changelog -n1 | awk '{print $$2}'  | sed "s/(//" | sed "s/)//" | sed "s/-.*//`

#additional defines which determine the compilation of conedy.
#chose CALENDARQUEUE if you want conedy tu use a calendarqueue instead of a relaxed heap as priority queue for events
#chose DOUBLE or LDOUBLE as basetype for all computations
defines = DOUBLE

.SILENT:	all

