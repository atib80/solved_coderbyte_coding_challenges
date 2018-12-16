@rem Simple build script for compiling and building simple C++ source code files
@echo off
pushd build
echo.
echo Building %* using Visual C++ compiler...
cl ..\%* -nologo -W4 -Fe%~n1 -std:c++17 -EHsc -O2 -Ot -Ox -Ob2 -Oy -Oi
echo.
echo Running %~n1.exe...
echo. 
.\%~n1.exe
popd