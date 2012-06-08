Installation
=======

Using Conedy’s Ubuntu/Debian repository
-------------------------------------------

Open ``/etc/apt/sources.list`` with an editor of your choice and add a line which is similar to the following::

   deb http://conedy.org/ubuntu/maverick maverick main

If you are not using Maverick, just replace ``maverick`` with your distribution’s codename (e.g. ``oneiric``) in this line. For Debian, replace ``ubuntu`` with ``debian``, and ``maverick`` with your distribution’s codename (e.g. ``squeeze``).


Add Conedy’s gpg-key to apt with the following command::

   wget http://conedy.org/download/conedy_gpg.pub -O - | sudo apt-key add -


And finally install Conedy via::

   sudo aptitude install conedy python-conedy


Con


Downloading Ubuntu/Debian packages
----------------------------------

Download the package(s) for your distribution from :ref:`Download`. The DEB file (e.g. ``conedy_0.18_amd64.deb``) can then be installed via::

   sudo dpkg -i conedy_0.18-1_amd64.deb
   sudo apt-get -f install



Three different debian packages are available with names ``conedy``, ``python-conedy`` and ``conedy-src``. The package ``conedy`` contains the script interpreter conedy, ``python-conedy`` installs the python bindings. Both packages only allow for the predefined node dynamics that ship with conedy. To allow for arbitrary node dynamics ``conedy-src`` needs to be installed, which depends (in the debian sense) on the libraries and compiler tools that are needed to built conedy. In addition to the full source code of conedy, ``conedy-src`` contains recompilation scripts and a global config-file. 





The recompilation mechanism that we chose for ``conedy`` will be explained in the following. For the global install of ``conedy``, the script interpreter compiled with the predefined node dynamics is installed into a global root-directory. User, may add node dynamics in which case, conedy is recompiled and the executable is stored in a directory in user-space, which is intended to have a higher priority in the system-path. In this way the executable the global ``conedy``-executable. Whenever a user calls ``recompileConedy`` or the ``conedy`` executable for the first time, the directory ~/.config/conedy  in the users's home directory is created, which contains a config file, a build directory for internal use, and a monitored directory ~/.config/conedy/addedNodes, in which new node dynamics can be stored. At every successive call of ``conedy``, this directory is monitored for all files which end with .cfg. Whenever one of these files changes or if a new file has been stored, ``conedy`` will recompile and restart itself.  If no config file is present at ~/.config/conedy/config.h, the global config file at /etc/conedy.config will be linked into this directory. However, this link can be replaced by a modified copy in order to change to way in which conedy is compiled. The syntax of the config-file is the same as for the config-file which is needed for a installation of conedy from the the tar-ball and the  relevant variables (``defines``, ``pythonBjam``, ``dirInstall`` and ``addedDir``) are explained in the following paragraph.



Building from source
--------------------

Conedy provides a Makefile, which handles compilation. Before building, a file named ``config.h`` should be created and filled with some basic configuration variables like installation directories. The file ``config.h.tmpl`` defines a template for this configuration file which defines a system-wide installation. Conedy does not need to be configured. The configure.sh, which ships with Conedy just prints a reminder to the console, that the file ``config.h`` needs to be edited.

The file ``config.h`` should define the following variables

- ``todo``

A whitespace seperated list of the targets you want to build. Should be an arbitrary subset of: python-conedy conedy conedy-src documentation debug condor python-conedy-root conedy-root.
Whenever the makefile targets  ``build``,  ``install``, ``test``, or ``uninstall`` are evoked, all targets in this subset are considered.  




- ``dirInstall``

The installation directory for Conedy’s script-interpreter and recompilation scripts.  Usually, you want to choose a directory which is in your path.

- ``dirSrc``

A directory for the installation of the Conedy sources.

- ``dirInstallRoot``


- ``buildDir``

XXX

- ``pythonBjam``

XXX

- ``globalConfig``

The filename for the config file of Conedy. During installation ``config.h`` is copied to this location, which allows you to change variables later.

- ``addedDir``

A directory which is monitored by Conedy for files which specify new nodes with user-added dynamics.

- ``numberCores``

The number of threads that should be used for recompilation of Conedy’s script interpreter (similar to ``make -j``).

- ``defines``

A collection of ``#define`` macros which influence compilation of the source code. At the moment only ``CALENDARQUEUE`` can be chosen in order to use the calendarqueue instead of a relaxed heap for the event integration. XXX DOUBLE


Dependencies
------------


To install Conedy from source, your system has to satisfy the following dependencies:


-  the GNU Scientific Library

    http://www.gnu.org/software/gsl/

-   boost-build, the build sytem of the Boost library
-   boost-iostreams used for automatic compression of file output

    http://www.boost.org/

-   make
-   C++ compiler


The script interpreter of Conedy  is created with Bisonc++ and flex. Therefore these tools need also be installed on your system.

-   Bisonc++, source code generation for a parser

    http://bisoncpp.sourceforge.net/

-   flex, source code generation for a scanner

    http://flex.sourceforge.net/


The python bindings of Conedy additionally depend on

-    boost-python

     http://www.boost.org/

If all dependencies are satisfied, building and installing can be issued by::

   $make; sudo make install


