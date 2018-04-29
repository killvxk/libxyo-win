@echo off

rem --- clean

echo ^> clean libxyo-win ^<

if exist bin\ rmdir /Q /S bin
if exist build\ rmdir /Q /S build
if exist lib\ rmdir /Q /S lib

