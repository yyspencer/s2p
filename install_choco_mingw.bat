@echo off

:: Install Chocolatey
echo Installing Chocolatey...
powershell -NoProfile -ExecutionPolicy Bypass -Command "iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))"

:: Refresh environment variables
refreshenv

:: Install MinGW
echo Installing MinGW...
choco install mingw -y

:: Add MinGW to PATH
echo Adding MinGW to PATH...
setx /M PATH "%PATH%;C:\MinGW\bin"

echo Installation completed.
pause