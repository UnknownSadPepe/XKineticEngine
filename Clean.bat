@ECHO OFF

REM XKCore
make -f "Makefile.XKCore.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM XKinetic
make -f "Makefile.XKinetic.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM XKTests
make -f "Makefile.XKTests.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM XKVulkan
make -f "Makefile.XKVulkan.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)
