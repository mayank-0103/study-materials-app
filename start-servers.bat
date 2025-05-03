::[Bat To Exe Converter]
::
::YAwzoRdxOk+EWAjk
::fBw5plQjdCyDJGyX8VAjFBZVVQWMAE+1EbsQ5+n//NarjWoyGus8d+8=
::YAwzuBVtJxjWCl3EqQJgSA==
::ZR4luwNxJguZRRnk
::Yhs/ulQjdF+5
::cxAkpRVqdFKZSzk=
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
::Zh4grVQjdCyDJGyX8VAjFBZVVQWMAE+1EbsQ5+n//Naro1gTV+pxfZfeug==
::YB416Ek+ZG8=
::
::
::978f952a14a936cc963da21a135fa983
@echo off
title Start Frontend and Backend Servers

:: Start Backend Server (hidden)
echo Starting Backend Server...
cd backend
start /B cmd /C "npm start >nul 2>&1"
cd ..

:: Start Frontend Server (hidden)
echo Starting Frontend Server...
cd frontend
start /B cmd /C "python -m http.server 5500 >nul 2>&1"
cd ..

:: Wait for 2 seconds
timeout /t 2 >nul

:: Open Frontend in Default Browser
echo Opening Frontend in default browser...
start http://localhost:5500

:: Display Status
echo ==========================================
echo Both servers have been started.
echo Backend: http://localhost:3000
echo Frontend: http://localhost:5500
echo ==========================================
pause