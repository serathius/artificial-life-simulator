#!/bin/sh
if [ ! -d lib/gtest ]; then
    if [ ! -e /tmp/gtest-1.7.0.zip ]; then
        wget https://googletest.googlecode.com/files/gtest-1.7.0.zip -P /tmp 1> /dev/null
    fi
    unzip /tmp/gtest-1.7.0.zip -d lib 1> /dev/null
    mv lib/gtest-1.7.0 lib/gtest
    rm /tmp/gtest-1.7.0.zip
fi
if [ ! -d lib/gmock ]; then
    if [ ! -e /tmp/gmock-1.7.0.zip ]; then
        wget https://googlemock.googlecode.com/files/gmock-1.7.0.zip -P /tmp 1> /dev/null
    fi
    unzip /tmp/gmock-1.7.0.zip -d lib 1> /dev/null
    mv lib/gmock-1.7.0 lib/gmock
    rm /tmp/gmock-1.7.0.zip
fi
make tests
bin/test.o
