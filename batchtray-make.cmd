@echo off

set CMDDIR=
set CMDFILE=%~f0
for /f "delims=" %%i in ("%CMDFILE%") do (
  set CMDDIR=%%~di%%~pi
)
cd %CMDDIR%

call batchtray-env.cmd

cd %SRCPATH%

rem qmake PREFIX+=%EXEPATH% batchtray.pro  <- fail
qmake batchtray.pro 
mingw32-make.exe release
mingw32-make.exe clean

echo Copy executable to %BINPATH%...
copy %SRCPATH%\%QTTARGET%\batchtray.exe      "%BINPATH%"

echo Copy Qt binaries to %BINPATH%...
copy "%MINGWBINPATH%\Qt5Core%QTPFX%.dll"     "%BINPATH%"
copy "%MINGWBINPATH%\Qt5Gui%QTPFX%.dll"      "%BINPATH%"
copy "%MINGWBINPATH%\Qt5Widgets%QTPFX%.dll"  "%BINPATH%"
copy "%MINGWBINPATH%\libgcc_s_dw2-1.dll"     "%BINPATH%"
copy "%MINGWBINPATH%\libstdc++-6.dll"        "%BINPATH%"
copy "%MINGWBINPATH%\libwinpthread-1.dll"    "%BINPATH%"
copy "%MINGWBINPATH%\libstdc++-6.dll"        "%BINPATH%"

if not exist "%BINPATH%\platforms" mkdir "%BINPATH%\platforms"
copy "%MINGWPLUGINSPATH%\platforms\qwindows.dll" "%BINPATH%\platforms"

rem move "debug" ../build
rem move "release" ../build

pause

rem E O F
