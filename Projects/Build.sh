#!/bin/bash

UNAME=`uname`

if [ "$UNAME" == "Darwin" ]; then
 
	PREMAKE="premake-osx"
	OSFOLDER="macosx"
fi
	
if [ "$UNAME" == "Linux" ]; then

	PREMAKE="premake"
	OSFOLDER="linux"
fi

chmod 777 ./${PREMAKE}

./${PREMAKE} clean
./${PREMAKE} gmake

if [ "$UNAME" == "Linux" ]; then
./${PREMAKE} xcode3
./${PREMAKE} xcode4
fi
