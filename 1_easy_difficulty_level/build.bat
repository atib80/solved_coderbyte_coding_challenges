@rem Simple build script for compiling and building simple C++ source code files
@echo off
pushd build
cl ..\%1 -nologo -W4 -Fetest -EHsc -O2 -Ot -Ox -Ob2 -Oy -Oi
.\test.exe
popd