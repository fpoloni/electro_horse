#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

CROSS_COMPILE=true

echo "Build Source Project"

if [ "$1" = "X86" ] || [ "$1" = "x86" ]; then
   CROSS_COMPILE=fasle
fi

export MD_CROSS_COMPILING=${CROSS_COMPILE}

MAKELIST="CMakeLists.txt"
BUILD_DIR="build"

if [ ! -e "$MAKELIST" ]; then
    echo "It is missing the " $MAKELIST
    exit 1
fi

if [ ! -d "$BUILD_DIR" ]; then
    mkdir build/
fi

cd $BUILD_DIR && cmake ../

make

echo -e "${GREEN}Success build${NC}"
unset ${CROSS_COMPILE}

cd ..
ln -sfn $(pwd)/$BUILD_DIR/eletro-app/Application EletroHorseApp

exit 0
