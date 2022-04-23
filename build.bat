@echo off

REM Change this to your visual studio's 'vcvars64.bat' script path
set MSVC_PATH="YOUR_PATH"

call %MSVC_PATH%\vcvars64.bat
    
if not exist .\build mkdir build
pushd .\build
cl ..\main.cpp /std:c++17 /Fe:undo-tracker.exe /Zi /EHsc
popd
