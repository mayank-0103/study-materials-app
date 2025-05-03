::[Bat To Exe Converter]
::
::YAwzoRdxOk+EWAnk
::fBw5plQjdG8=
::YAwzuBVtJxjWCl3EqQJgSA==
::ZR4luwNxJguZRRnk
::Yhs/ulQjdF+5
::cxAkpRVqdFKZSDk=
::cBs/ulQjdF+5
::ZR41oxFsdFKZSDk=
::eBoioBt6dFKZSDk=
::cRo6pxp7LAbNWATEpCI=
::egkzugNsPRvcWATEpCI=
::dAsiuh18IRvcCxnZtBJQ
::cRYluBh/LU+EWAnk
::YxY4rhs+aU+JeA==
::cxY6rQJ7JhzQF1fEqQJQ
::ZQ05rAF9IBncCkqN+0xwdVs0
::ZQ05rAF9IAHYFVzEqQJQ
::eg0/rx1wNQPfEVWB+kM9LVsJDGQ=
::fBEirQZwNQPfEVWB+kM9LVsJDGQ=
::cRolqwZ3JBvQF1fEqQJQ
::dhA7uBVwLU+EWDk=
::YQ03rBFzNR3SWATElA==
::dhAmsQZ3MwfNWATElA==
::ZQ0/vhVqMQ3MEVWAtB9wSA==
::Zg8zqx1/OA3MEVWAtB9wSA==
::dhA7pRFwIByZRRnk
::Zh4grVQjdCuDJHSF7UM+I1tmTQ6+H1ifRps13MzHveSD4n4YWecsbIrJmvzccLJGo3nHRqYPlisKyItBTCtKcRiubRt0gFJ1s2aWPtOZjxz1RVjE9U4iDWBmlC3VlC5b
::YB416Ek+ZG8=
::
::
::978f952a14a936cc963da21a135fa983
@echo off
title Stop Frontend and Backend Servers

:: Stop Backend Server
echo Stopping Backend Server...
for /f "tokens=5" %%a in ('netstat -ano ^| find ":3000" ^| find "LISTENING"') do taskkill /PID %%a /F >nul 2>&1

:: Stop Frontend Server
echo Stopping Frontend Server...
for /f "tokens=5" %%a in ('netstat -ano ^| find ":5500" ^| find "LISTENING"') do taskkill /PID %%a /F >nul 2>&1

:: Display Status
echo ==========================================
echo Both servers have been stopped.
echo ==========================================
pause