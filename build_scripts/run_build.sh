#!/bin/bash

cd ..
mkdir build
cd build
cmake -DCMAKE_CXX_COMPILER=mpic++ ..
make -j 2
