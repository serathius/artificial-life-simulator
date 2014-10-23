#!/bin/sh
if [ ! -d lib/glfw ]; then
    if [ ! -e /tmp/glfw-3.0.4.zip ]; then
        wget http://softlayer-ams.dl.sourceforge.net/project/glfw/glfw/3.0.4/glfw-3.0.4.zip -P /tmp 1> /dev/null
    fi
    unzip /tmp/glfw-3.0.4.zip -d lib 1> /dev/null
    mv lib/glfw-3.0.4 lib/glfw
    rm /tmp/glfw-3.0.4.zip
fi
cd lib/glfw
cmake .
make
sudo make install
cd ../..
