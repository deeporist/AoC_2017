@echo on
setlocal ENABLEDELAYEDEXPANSION
title %cd%
cls

call Day8_set.bat
cls
call Day8_cal_ex.bat
cls
call Day8_last.bat
pause

for /f "tokens=1,2,3,4,5,6 delims= " %%a in (Day8_ex.txt) do (
@echo if $%%d$ %%e %%f #set /a %%a=$%%a$%%b@ >> Day8_cal.txt
@echo if $%%a$ gtr ~max~ #set maxn=%%a * set max=$%%a$@ >> Day8_cal.txt
)
pause


call Day8_set.bat
cls
call Day8_cal.bat
cls
call Day8_last.bat

for /f "tokens=1,2,3,4,5,6 delims= " %%a in (Day8_ex.txt) do (
@echo if $%%d$ %%e %%f #set /a %%a=$%%a$%%b@ >> Day8_cal.txt
@echo if $%%a$ gtr ~max~ #set maxn=%%a * set max=$%%a$@ >> Day8_cal.txt
)
pause

for /f %%q in (Day8_index.txt) do (
@echo if $%%q$ gtr ~max~ @set maxn=%%q * set max=$%%q$# >> Day8_last.txt
)
pause


for /f %%a in (Day8_index.txt) do (
@echo echo %%a $%%a$ >> Day8_show.txt
)
pause


for /f %%a in (Day8_index.txt) do (
@echo set %%a=0 >> Day8_set.txt
)
pause

for /f %%a in (Day8_index.txt) do (
set n=%%a
for /f %%z in ('findstr /m /c:"!n!" Day8_register.txt') do (
set n2=%%z
if /i !n2! neq Day8_register.txt (@echo !n! 0 >> Day8_register.txt)
pause
)
pause
)
pause


for /f %%a in (Day8_index.txt) do (
set n=%%a
for /f %%z in ('findstr /m /c:"!n!" Day8_index.txt') do (
if /i %%z equ Day8_index.txt (@echo FUCK!!!!!!!)
)
pause
)
pause

for /f "delims= " %%a in (Day8.txt) do (
@echo %%a >> Day8_index.txt
)
pause

call Day8_set.bat
cls
call Day8_cal.bat
cls
call Day8_show.bat


for /f "tokens=1,2,3,4,5,6 delims= " %%a in (Day8_ex.txt) do (
@echo if $%%d$ %%e %%f #set /a %%a=$%%a$%%b@ >> Day8_cal.txt
)
pause

for /f "delims= " %%a in (Day8_register.txt) do (
@echo echo %%a $%%a$ >> Day8_show.txt
)
pause

for /f "delims= " %%y in (Day8.txt) do (
set n=%%y
for /f "skip=1 delims=" %%z in ('find /c "!n!" Day8_register.txt') do (
set x=%%z
if !x:~-1! equ 0 (@echo !n! 0 >> Day8_register.txt)
)
)
pause

for /f "delims=" %%a in (Day8_register.txt) do (
@echo set %%a >> Day8_set.txt
)
pause

for /f "tokens=6 delims= " %%a in (Day8.txt) do (
@echo %%a
pause
)
pause