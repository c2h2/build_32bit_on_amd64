#!/bin/bash

echo "Building C++ demo for 64-bit architecture..."

# Compile for native 64-bit using g++
g++ -std=c++14 -o demo_64bit demo.cpp

if [ $? -eq 0 ]; then
    echo "64-bit C++ build successful!"
    echo "Binary: demo_64bit"
else
    echo "64-bit C++ build failed!"
    exit 1
fi