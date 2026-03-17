@echo off
mkdir bin 2>nul
mkdir lib 2>nul

echo Compiling source files...
for %%f in (src\*.c) do (
    gcc -c %%f -Iinclude -o bin\%%~nf.o
)

echo Creating static library...
ar rcs lib\libaes.a bin\*.o

echo Done.