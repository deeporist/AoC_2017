setlocal ENABLEDELAYEDEXPANSION
@echo off


for /f %%a in (Day20_last.txt) do (
findstr /x /n /c:"%%a" Day20_last.txt
)
pause