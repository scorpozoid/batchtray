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

set CMDDIR=
set CMDFILE=%~f0
for /f "delims=" %%i in ("%CMDFILE%") do (
  set CMDDIR=%%~di%%~pi
)
cd %CMDDIR%

cd %CMDDIR%
cd src
set EXEPATH=%CD%\%QTTARGET%

cd %CMDDIR%
cd src
rem qmake PREFIX+=%EXEPATH% batchtray.pro  <- fail
qmake batchtray.pro 
mingw32-make.exe release

echo Copy Qt binaries...
copy "%MINGWBINPATH%\Qt5Core%QTPFX%.dll"     "%EXEPATH%"
copy "%MINGWBINPATH%\Qt5Gui%QTPFX%.dll"      "%EXEPATH%"
copy "%MINGWBINPATH%\Qt5Widgets%QTPFX%.dll"  "%EXEPATH%"
copy "%MINGWBINPATH%\libgcc_s_dw2-1.dll"     "%EXEPATH%"
copy "%MINGWBINPATH%\libstdc++-6.dll"        "%EXEPATH%"
copy "%MINGWBINPATH%\libwinpthread-1.dll"    "%EXEPATH%"
copy "%MINGWBINPATH%\libstdc++-6.dll"        "%EXEPATH%"

rem move "debug" ../build
rem move "release" ../build

mingw32-make.exe clean

pause

rem E O F
