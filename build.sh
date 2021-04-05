#!/bin/bash

rm -r build
mkdir build
cd build

cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../

make -j

cp ./test_stb ../
