
rem remove all edges
rm generated*


rem generate sourcecode
for /r %%i in (addedNodes/*.cfg) do python addNewNode.py addedNodes/%%~ni%%~xi   


rem paste documentation into docstrings.h
setlocal enabledelayedexpansion
echo  //generatedBy makeDocstringsWindows.bat > docstrings.h
cd testing
for /r %%i in (*.rst) do (
    python ../makeDocstringsWindows.py "%%i"
)
cd ..

xxd -i config.h.tmpl > string_config.h
echo WINDOWS > dirInstall.h
xxd -i dirInstall.h >> string_config.h