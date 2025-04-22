@echo off
setlocal
set APPNAME=raylib_dk_console
set APPPATH=build\Debug\%APPNAME%.exe
set EXECUTABLE=%APPNAME%.exe

if not exist %APPPATH% (
    echo Executable not found! Please build the project first.
    exit /b 1
)

echo Running %APPNAME%...

cd build\Debug\

%EXECUTABLE%

endlocal