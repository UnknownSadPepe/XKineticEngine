#!/bin/bash

make -f Makefile.XKCore.linux clean

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
	echo "Error:"$ERRORLEVEL && exit
fi

make -f Makefile.XKMath.linux clean

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
	echo "Error:"$ERRORLEVEL && exit
fi

make -f Makefile.XKinetic.linux clean

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ]
then
	echo "Error:"$ERRORLEVEL && exit
fi

make -f Makefile.XKVulkan.linux clean

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ] 
then
	echo "Error:"$ERRORLEVEL && exit
fi

make -f Makefile.XKTests.linux clean

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ] 
then
	echo "Error:"$ERRORLEVEL && exit
fi

