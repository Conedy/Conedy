Installation and Recompilation
==============================

Ubuntu/Debian packages
++++++++++++++++++++++

Using Conedy’s repository
-------------------------

Open ``/etc/apt/sources.list`` with an editor of your choice and add a line which is similar to the following::

	deb http://conedy.org/ubuntu/maverick maverick main

If you are not using Maverick, just replace ``maverick`` with your distribution’s codename (e.g. ``oneiric``) in this line. For Debian, replace ``ubuntu`` with ``debian``, and ``maverick`` with your distribution’s codename (e.g. ``squeeze``).


Add Conedy’s gpg-key to apt with the following command::

	wget http://conedy.org/download/conedy_gpg.pub -O - | sudo apt-key add -


And finally install Conedy via::

	sudo aptitude install conedy python-conedy conedy-src

(The different packages are described further below)


Downloading packages
--------------------

Download the package(s) for your distribution from :ref:`download`. The DEB file (e.g. ``conedy_0.18_amd64.deb``) can then be installed via::

	sudo dpkg -i conedy_0.18-1_amd64.deb
	sudo apt-get -f install

The different packages
----------------------

Three different Debian packages are available with names ``conedy``, ``python-conedy`` and ``conedy-src``. The package ``conedy`` contains the script interpreter conedy, ``python-conedy`` installs the python bindings. Both packages only allow for the predefined node dynamics that ship with conedy. To allow for arbitrary node dynamics ``conedy-src`` needs to be installed, which depends (in the debian sense) on the libraries and compiler tools that are needed to built conedy. In addition to the full source code of conedy, ``conedy-src`` contains recompilation scripts (see :ref:`recompilation`) and a global config-file.


Building from source
++++++++++++++++++++

You can obtain the latest version of Conedy’s source from `its Github repository`_, for example with the following command::

	git clone http://github.com/Wrzlprmft/Conedy

.. _its Github repository: http://github.com/Conedy/Conedy


Conedy provides a Makefile, which handles compilation (``make; make install``).

Configuring the source
----------------------

Before building, a file named ``config.h`` should be created and filled with some basic configuration variables like installation directories. The file ``config.h.tmpl`` defines a template for this configuration file which defines a system-wide installation. Conedy does not need to be configured. The ``configure.sh``, which ships with Conedy just prints a reminder to the console, that the file ``config.h`` needs to be edited.

The file ``config.h`` should define the following variables

- ``todo``: A whitespace-seperated list of the targets you want to build. Should be an arbitrary subset of: ``python-conedy``, ``conedy``, ``conedy-src``, ``documentation``, ``debug``, ``condor``, ``python-conedy-root``, ``conedy-root``. Whenever the makefile targets ``build``,  ``install``, ``test`` or ``uninstall`` are evoked, all targets in this subset are considered. The targets suffixed with ``-root`` are intended for a global installation (which requires superuser rights).

- ``dirInstall``: The installation directory for Conedy’s script-interpreter and recompilation scripts. Usually, you want to choose a directory which is in your ``PATH``. A common choice is ``~/bin``, which may however not be in your ``PATH`` by default (look e.g. `here`_ for one of the myriad of how-tos).

- ``dirSrc``: A directory for the installation of the Conedy sources.

- ``dirInstallRoot`` XXX

- ``buildDir`` XXX

- ``pythonBjam`` XXX

- ``globalConfig``: The filename for the global config file of Conedy. During installation ``config.h`` is copied to this location, which allows you to change variables later.

- ``addedDir``: A directory which is monitored by Conedy for files which specify new nodes with user-added dynamics.

- ``numberCores``: The number of threads that should be used for recompilation of Conedy’s script interpreter (similar to ``make -j``). (Python’s Distutils do not support this.)

- ``defines``: A white-space seperated collection of ``#define`` macros which influence compilation of the source code. ``CALENDARQUEUE`` can be chosen in order to use the calendar queue instead of a relaxed heap for the event integration. Either DOUBLE or LDOUBLE can be chosen to set Conedy’s basic data type to double or long double, respectively. The latter does, however, not work with GSL-based integrators.


.. _here: http://askubuntu.com/questions/60218/how-to-add-a-directory-to-my-path



Dependencies
------------

To install Conedy from source, your system has to satisfy the following dependencies:

- the GNU Scientific Library (http://www.gnu.org/software/gsl/)
- Boost Build, the build sytem of the Boost library (http://www.boost.org/)
- Boost Iostreams used for automatic compression of file output (http://www.boost.org/)
- Make
- C++ compiler

The script interpreter of Conedy is created with Bisonc++ and Flex. Therefore these tools need also be installed on your system.

- Bisonc++: source code generation for a parser (http://bisoncpp.sourceforge.net/)
- Flex, source code generation for a scanner (http://flex.sourceforge.net/)

The python bindings of Conedy additionally depend on

- Boost Python (http://www.boost.org/)



.. _recompilation:

Recompilation
+++++++++++++

In the following, we explain Conedy’s recompilation mechanism.

For the global install of Conedy, the script interpreter compiled with the predefined node dynamics is installed into a global root-directory.
If a user adds node dynamics (see :ref:`addingNewNodes`), Conedy is recompiled and the executable is stored in a directory in user-space, which is intended to have a higher priority in the system ``PATH``.
This way the executable is preferred to the global Conedy executable.
Whenever a user calls ``recompileConedy`` or ``conedy`` for the first time, the directory ``~/.config/conedy`` in the users's home directory is created, which contains a config file, a build directory for internal use, and a monitored directory ``~/.config/conedy/addedNodes``, in which new node dynamics can be stored.
At every successive call of ``conedy``, this directory is monitored for all files which end with ``.cfg``.
Whenever one of these files changes or if a new file has been stored, Conedy will recompile and restart itself.
If no config file is present at ``~/.config/conedy/config.h``, the global config file at ``/etc/conedy.config`` will be linked into this directory.
However, this link can be replaced by a modified copy in order to change how Conedy is compiled.
The syntax of the config file is the same as for the config file which is needed for an installation of conedy from source and the  relevant variables (``defines``, ``pythonBjam``, ``dirInstall`` and ``addedDir``) are explained above.


