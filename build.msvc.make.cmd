@echo off

rem --- make

echo ^> make libxyo-win ^<

goto Make
:ErrorMake
echo Error: make
goto :eof
:Make

set XLIB_STATIC= 
set XLIB_STATIC= %XLIB_STATIC% --use-project=libxyo-core.static
set XLIB_STATIC= %XLIB_STATIC% --use-project=libxyo-pixel32.static

set XLIB= 
set XLIB= %XLIB% --use-project=libxyo-core
set XLIB= %XLIB% --use-project=libxyo-pixel32
set XLIB= %XLIB% --use-lib=libpng
set XLIB= %XLIB% --use-lib=libz
set XLIB= %XLIB% --use-lib=secur32
set XLIB= %XLIB% --use-lib=adsiid
set XLIB= %XLIB% --use-lib=activeds

xyo-cc --mode=%ACTION% --lib libxyo-win --source-is-separate %XLIB_STATIC%
IF ERRORLEVEL 1 goto ErrorMake
xyo-cc --mode=%ACTION% --dll libxyo-win --no-version --source-is-separate %XLIB%
IF ERRORLEVEL 1 goto ErrorMake


