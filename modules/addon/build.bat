@echo off

if not exist .\build\win32 mkdir .\build\win32
cmake -A Win32 -S . -B .\build\win32
cmake --build .\build\win32 --config Release
copy /Y .\build\win32\Release\addon.dll ..\..\build\win32\Release\addon.dll
