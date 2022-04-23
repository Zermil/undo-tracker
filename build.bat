@echo off

set MY_PATH=%~dp0

REM Change this to your visual studio's 'vcvars64.bat' script path
set MSVC_PATH="YOUR_PATH"

call %MSVC_PATH%\vcvars64.bat

pushd %MY_PATH%\build
cl ..\src\main.cpp /I../deps/SDL2/include /std:c++17 /Fe:undo-tracker.exe /Zi /EHsc /link ..\deps\SDL2\lib\SDL2.lib ..\deps\SDL2\lib\SDL2main.lib ..\deps\SDL2\lib\SDL2_ttf.lib
popd
