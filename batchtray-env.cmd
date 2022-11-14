@echo off

rem QTPFX=d
rem QTTARGET=debug
set QTPFX=
set QTTARGET=release
set QTFWPATH=C:\Qt\5.11.0
set MINGWTOOLPATH=%QTFWPATH%\Tools\mingw530_32\bin
set MINGWPATH=%QTFWPATH%\5.11.0\mingw53_32
set MINGWBINPATH=%MINGWPATH%\bin
set MINGWPLUGINSPATH=%MINGWPATH%\plugins

set PATH=%MINGWTOOLPATH%;%PATH%
set PATH=%MINGWBINPATH%;%PATH%

set BINPATH=
set SRCPATH=

set CMDDIR=
set CMDFILE=%~f0
for /f "delims=" %%i in ("%CMDFILE%") do (
  set CMDDIR=%%~di%%~pi
)

cd %CMDDIR%
cd src
set SRCPATH=%CD%

cd %CMDDIR%
if not exist bin mkdir bin
cd bin
set BINPATH=%CD%

rem E O F
