@echo off

set CMDDIR=
set CMDFILE=%~f0
for /f "delims=" %%i in ("%CMDFILE%") do (
  set CMDDIR=%%~di%%~pi
)
cd %CMDDIR%

call batchtray-env.cmd

cd %BINPATH%

batchtray.exe

rem E O F
