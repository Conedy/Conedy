Installation and Recompilation
==============================

Ubuntu/Debian packages
++++++++++++++++++++++

Using Conedy’s repository
-------------------------

Open ``/etc/apt/sources.list`` with an editor of your choice and add a line which is similar to the following::

	deb http://conedy.org/ubuntu/maverick maverick main

If you are not using Maverick, just replace ``maverick`` with your distribution’s codename (e.g. ``oneiric``) in this line. For Debian, replace ``ubuntu`` with ``debian``, and ``maverick`` with your distribution’s codename (e.g. ``squeeze``).


Add Conedy’s GPG key to apt with the following command::

	wget http://conedy.org/download/conedy_gpg.pub -O - | sudo apt-key add -

And finally update your package index and install Conedy via::

	sudo apt-get update && sudo apt-get install conedy python-conedy conedy-src

(The different packages are described further below)


Downloading packages
--------------------

Download the package(s) for your distribution from :ref:`download`. The DEB file (e.g. ``conedy_0.18_amd64.deb``) can then be installed via::

	sudo dpkg -i conedy_0.18-1_amd64.deb
	sudo apt-get -f install

The different packages
----------------------

Three different Debian packages are available with names ``conedy``, ``python-conedy`` and ``conedy-src``. The package ``conedy`` contains the script interpreter conedy, ``python-conedy`` installs the Python bindings. Both packages only allow for the predefined node dynamics that ship with conedy. To use user-defined node dynamics, ``conedy-src`` needs to be installed, which depends (in the Debian sense) on the libraries and compiler tools that are needed to build conedy. In addition to the full source code of conedy, ``conedy-src`` contains recompilation scripts (see :ref:`recompilation`) and a global config file.

.. _building:

Building from source
++++++++++++++++++++

(See the :ref:`download section<sourcedownload>` for instructions on dowloading the source.)

Conedy provides a Makefile, which handles compilation (``make; make install``).

Configuring the source
----------------------

Before building, you may want to take a look at the configuration file ``config.h``, which contains basic configuration variables like installation directories.
By default ``config.h`` is set for global installation, but can also be set for an installation to the user space (see below)

Conedy does not need to be configured.
The ``configure.sh``, which ships with Conedy just prints a reminder to the console, that the file ``config.h`` should be edited.

The file ``config.h`` should define the following variables

- ``todo``: A whitespace-seperated list of the targets you want to build. Should be an arbitrary subset of: ``python-conedy``, ``conedy``, ``conedy-src``, ``documentation``, ``debug``, ``condor``, ``python-conedy-root``, ``conedy-root``. Whenever the Makefile targets ``build``,  ``install``, ``test`` or ``uninstall`` are evoked, all targets in this subset are considered. The targets suffixed with ``-root`` are intended for a global installation (which requires superuser rights).

- ``dirInstall``: The installation directory for Conedy’s script-interpreter and recompilation scripts. Usually, you want to choose a directory which is in your ``PATH``. A common choice is ``${HOME}/bin``, which you may however have to add to your ``PATH`` first (the internet offers a myriad of instruction for this, e.g. `this one`_.

- ``dirSrc``: A directory for the installation of the Conedy sources.

- ``dirInstallRoot``: A directory in which conedy is installed if conedy-root ist set in todo.

- ``buildDir``: The directory in which conedy rebuilds, when new nodes are added

- ``pythonBjam``: If set to true, Coendy will rebuild the python extension using bjam instead of distutils. While this is much faster, it is experimental for the moment.

- ``globalConfig``: The filename for the global config file of Conedy. During installation ``config.h`` is copied to this location, which allows you to change variables later.

- ``addedDir``: A directory which is monitored by Conedy for files which specify new nodes with user-added dynamics.

- ``numberCores``: The number of threads that should be used for recompilation of Conedy’s script interpreter (similar to ``make -j``). (The Python bindings cannot compiled parallely since Distutils do not support this.)

- ``defines``: A white-space seperated collection of ``#define`` macros which influence compilation of the source code. ``CALENDARQUEUE`` can be chosen in order to use the calendar queue instead of a relaxed heap for the event integration. Either ``DOUBLE`` or ``LDOUBLE`` can be chosen to set Conedy’s basic data type to double or long double, respectively. The latter does, however, not work with GSL-based integrators.


.. _this one: http://askubuntu.com/questions/60218/how-to-add-a-directory-to-my-path



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

In the following, we explain Conedy’s recompilation mechanism, which allows for the efficient use of user-defined node dynamics (see :ref:`addingNewNodes`). To allow recompilation, the todo variable in config.h should contain conedy-root and conedy-src when building and installing Conedy. Analogously, to allow recompilation of the python module, python-conedy-root and conedy-src should be part of the todo variable in config.h. 

For the global install of Conedy, the script interpreter compiled with the predefined node dynamics is installed into a global root-directory, accessible to all users. If a user adds node dynamics, the recompiled executable ``conedy`` is stored in a directory in user-space (defaults to ``~/bin/``), which is intended to have a higher priority in the system ``PATH``. This way the executable is preferred to the global Conedy executable. The recompiled python module will be installed with distutils using the command line option ``--local`` which also installs the module in a directory with higher priority than the global module.

Whenever a user calls ``conedy`` for the first time (or if ``conedy`` is imported the first time into python), the directory ``${HOME}/.config/conedy`` in the users's home directory is created, which contains a config file, a build directory for internal use, and a monitored directory ``${HOME}/.config/conedy/addedNodes``, in which new node dynamics can be stored. At every successive call of ``conedy``, this directory is monitored for all files which end with ``.cfg``. Whenever one of these files changes or if a new file has been stored, Conedy will recompile and restart itself.

If no config file is present at ``${HOME}/.config/conedy/config.h``, the global config file at ``/etc/conedy.config`` will be linked into this directory.
However, this link can be replaced by a modified copy in order to change how Conedy is compiled.
The syntax of the config file is the same as for the config file which is needed for an installation of Conedy from source and the  relevant variables (``defines``, ``pythonBjam``, ``dirInstall`` and ``addedDir``) are explained above.

The recompilation mechanism uses scripts ``recompileConedy`` and ``recompilePython-Conedy`` which are called by ``conedy`` on startup or import to python. As an alternative way to issue recompilation, they can also called by hand. Note that the scripts return true after a sucessful recompilation and false if no recompilation was necessary or if the it encounters problems.





