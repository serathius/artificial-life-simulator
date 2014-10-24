#!/bin/sh
./install.sh
if [ ! -e external/lib/libgtest.a ]; then
    if [ ! -d /tmp/gtest-1.7.0 ]; then
        if [ ! -e /tmp/gtest-1.7.0.zip ]; then
            wget https://googletest.googlecode.com/files/gtest-1.7.0.zip -P /tmp 1> /dev/null
        fi
        unzip /tmp/gtest-1.7.0.zip -d /tmp 1> /dev/null
    fi
    if [ ! -d /tmp/gmock-1.7.0 ]; then
        if [ ! -e /tmp/gmock-1.7.0.zip ]; then
            wget https://googlemock.googlecode.com/files/gmock-1.7.0.zip -P /tmp 1> /dev/null
        fi
        unzip /tmp/gmock-1.7.0.zip -d /tmp 1> /dev/null
    fi
    g++ -isystem /tmp/gtest-1.7.0/include -isystem /tmp/gmock-1.7.0/include -I /tmp/gtest-1.7.0 -I /tmp/gmock-1.7.0 -c /tmp/gtest-1.7.0/src/gtest-all.cc -o /tmp/gtest-1.7.0/gtest-all.o
    g++ -isystem /tmp/gtest-1.7.0/include -isystem /tmp/gmock-1.7.0/include -I /tmp/gtest-1.7.0 -I /tmp/gmock-1.7.0 -c /tmp/gmock-1.7.0/src/gmock-all.cc -o /tmp/gmock-1.7.0/gmock-all.o
    ar -rv external/lib/libgtest.a /tmp/gtest-1.7.0/gtest-all.o /tmp/gmock-1.7.0/gmock-all.o
    cp -r /tmp/gmock-1.7.0/include external/
    cp -r /tmp/gtest-1.7.0/include external/
fi
./install.sh
make tests
bin/tests.o
