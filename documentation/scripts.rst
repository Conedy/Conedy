.. _scriptInterpreter :

The built-in script interpreter
///////////////////////////////

The built-in script interpreter may be useful if you want to distribute computations onto a cluster as the interpreter can easily be linked statically (in contrast to python). In addition, it has support for creating `condor`_  dagman job files, converting the iterations of vectorizable loops into different jobs. Condor is a job management system developed at the Computer Science Department of the University of Wisconsin.

Most of the following description applies to both interfaces; every function of the python-binding corresponds to a function (of the same name) of the built-in interpreter. The main difference in syntax is:

-  add a ";" at the end of every command.

See the testing directory of the source code for example files. If you are familiar with bison/flex grammar files you may also look into Parser.yy and Scanner.ll of Conedy's source code. Although the built-in interpreter supports C-contstructs (like if statements or loops), it may still be limited in some cases.
