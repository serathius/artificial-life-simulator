#!/bin/bash

TEMP_DIR=/tmp
BUILD_DIR=build
GMOCK="gmock-1.7.0"
DEPENDENCIES=($GMOCK)
declare -A URLS
URLS["$GMOCK"]="https://googlemock.googlecode.com/files/gmock-1.7.0.zip"
declare -A RENAME
RENAME["$GMOCK"]="gmock"

mkdir -p $BUILD_DIR
for DEPENDENCY in ${DEPENDENCIES[*]}; do
    if [ ! -d $BUILD_DIR/${RENAME[$DEPENDENCY]} ]; then
        if [ ! -e "$TEMP_DIR/$DEPENDENCY.zip" ]; then
            wget -O "$TEMP_DIR/$DEPENDENCY.zip" ${URLS[$DEPENDENCY]} 1> /dev/null
        fi

        unzip $TEMP_DIR/$DEPENDENCY.zip -d $BUILD_DIR/ 1> /dev/null
        mv $BUILD_DIR/$DEPENDENCY $BUILD_DIR/${RENAME[$DEPENDENCY]}
    fi
done
./install.sh
cmake .
make unittests
./unittests
