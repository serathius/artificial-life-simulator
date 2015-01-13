#!/bin/sh

EXTERNAL_DIR=external
EXTERNAL_LIBDIR=external/lib
PROJECTDIR=$(pwd)

if [ ! -e $PROJECTDIR/external/lib/libglfw3.a ]; then
    if [ ! -d /tmp/glfw-3.0.4 ]; then
        if [ ! -e /tmp/glfw-3.0.4.zip ]; then
            wget http://softlayer-ams.dl.sourceforge.net/project/glfw/glfw/3.0.4/glfw-3.0.4.zip -P /tmp 1> /dev/null
        fi
        unzip /tmp/glfw-3.0.4.zip -d /tmp 1> /dev/null
    fi
    cd /tmp/glfw-3.0.4
    cmake -DCMAKE_INSTALL_PREFIX=. .
    make
    make install
    cd $PROJECTDIR
    mkdir -p $EXTERNAL_DIR $EXTERNAL_LIBDIR
    cp /tmp/glfw-3.0.4/lib/libglfw3.a $PROJECTDIR/$EXTERNAL_LIBDIR/
    cp -r /tmp/glfw-3.0.4/include $PROJECTDIR/external/
fi
