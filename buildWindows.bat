call "C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\vcvarsall.bat"


set INCLUDE=%INCLUDE%;C:\Program Files (x86)\boost\boost_1_46_1;C:\gsl-1.14\include\;
set LIB=%LIB%;C:\Program Files (x86)\boost\boost_1_46_1\lib;C:\gsl-1.14\lib\;

set > variablenDebug
python.exe setup.py bdist_wininst > errors

rem bjam --user-config.jam= user-config.jam conedy
