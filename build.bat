@echo off

set MY_PATH=%~dp0

REM Change this to your visual studio's 'vcvars64.bat' script path
set MSVC_PATH="YOUR_PATH"
call %MSVC_PATH%\vcvars64.bat

pushd %MY_PATH%\build

set SDL2_PATH="..\deps\SDL2"
set SDL2_LINK="%SDL2_PATH%\lib\SDL2.lib" "%SDL2_PATH%\lib\SDL2main.lib" "%SDL2_PATH%\lib\SDL2_ttf.lib"

cl ..\src\main.cpp /I%SDL2_PATH%\include /std:c++17 /EHsc %* /Fe:undo-tracker.exe /link user32.lib %SDL2_LINK% /SUBSYSTEM:windows /ENTRY:mainCRTStartup

popd