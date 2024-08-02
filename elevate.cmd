@echo off
:: Check for elevation
net session >nul 2>&1
if %errorlevel% neq 0 (
    echo Requesting administrative privileges...
    powershell -Command "Start-Process cmd -ArgumentList '/k cd %cd%' -Verb RunAs"
    exit
)
echo You have administrative privileges.