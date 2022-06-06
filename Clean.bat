@ECHO OFF

REM XKCore
make -f "Makefile.XKCore.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM XKMath
make -f "Makefile.XKMath.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM XKinetic
make -f "Makefile.XKinetic.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM XKVulkan
make -f "Makefile.XKVulkan.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM XKDirectX12
make -f "Makefile.XKDirectX12.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM XKEditor
make -f "Makefile.XKEditor.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)

REM XKTests
make -f "Makefile.XKTests.win32" clean
IF %ERRORLEVEL% NEQ 0 (echo Error:%ERRORLEVEL% && exit)
