setlocal ENABLEDELAYEDEXPANSION
@echo off
for /f %%a in (Day20_time_ex.txt) do (
@echo %%a
for /f "delims=" %%b in (Day20_ex_test.txt) do (
set i=%%b
if /i !i:~-2! equ %%a (@echo !i!>>z:\Day20_ex_%%a.txt)
)
)
pause