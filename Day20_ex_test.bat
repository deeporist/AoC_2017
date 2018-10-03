setlocal ENABLEDELAYEDEXPANSION
@echo off
for /f "tokens=3 delims= " %%a in (Day20_ex_test.txt) do (
@echo %%a
for /f "delims=" %%b in ('find /c "%%a" H:\masm\"CC++"\Day20_time.txt') do (
set i=%%b
@echo !i:~-1!
if /i !i:~-1! equ 0 (@echo %%a>>H:\masm\"CC++"\Day20_time.txt)
)
)