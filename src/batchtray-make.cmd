@echo off

set PATH=C:\Qt\Qt5.11.0\5.11.0\mingw53_32\bin;%PATH%
set PATH=C:\Qt\Qt5.11.0\Tools\mingw530_32\bin;%PATH%
set PATH=C:\Qt\5.11.0\5.11.0\mingw53_32\bin;%PATH%
set PATH=C:\Qt\5.11.0\Tools\mingw530_32\bin;%PATH%

set CMDDIR=
set CMDFILE=%~f0
for /f "delims=" %%i in ("%CMDFILE%") do (
  set CMDDIR=%%~di%%~pi
)

cd %CMDDIR%

qmake batchtray.pro
mingw32-make.exe

pause

rem E O F
