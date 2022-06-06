#!/bin/bash

make -f Makefile.XKCore.linux all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ] 
then
	echo "Error:"$ERRORLEVEL && exit
fi

make -f Makefile.XKMath.linux all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ] 
then
	echo "Error:"$ERRORLEVEL && exit
fi

make -f Makefile.XKVulkan.linux all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ] 
then
	echo "Error:"$ERRORLEVEL && exit
fi

make -f Makefile.XKinetic.linux all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ] 
then
	echo "Error:"$ERRORLEVEL && exit
fi

make -f Makefile.XKTests.linux all

ERRORLEVEL=$?
if [ $ERRORLEVEL -ne 0 ] 
then
	echo "Error:"$ERRORLEVEL && exit
fi

