#!/bin/bash

echo "Building C++ demo for 32-bit architecture..."

# Cross-compile for 32-bit using i686-linux-gnu-g++
i686-linux-gnu-g++ -std=c++14 -o demo_32bit demo.cpp

if [ $? -eq 0 ]; then
    echo "32-bit C++ build successful!"
    echo "Binary: demo_32bit"
else
    echo "32-bit C++ build failed!"
    exit 1
fi