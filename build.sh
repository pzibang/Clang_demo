#!/bin/bash

mkdir build

rm -rf ./build/*

cd build

cmake ../ -DCMAKE_TOOLCHAIN_FILE=./linux.toolchain.cmake && make VERBOSE=1
