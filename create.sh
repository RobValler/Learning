#!/bin/sh
set -e
rm -rf build || true
mkdir build
cd build
conan install .. 
#conan build .. 
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j16

