#!/bin/bash

echo "Building Qt5 demo for native 64-bit architecture..."

# Create build directory
mkdir -p build/qt_64bit
cd build/qt_64bit

# Use native qmake to configure for 64-bit build
if command -v qmake-qt5 >/dev/null 2>&1; then
    echo "Using qmake-qt5..."
    qmake-qt5 ../../src/qt_demo_simple.pro
else
    echo "Using qmake..."
    qmake ../../src/qt_demo_simple.pro
fi

# Build with make
if make; then
    echo "64-bit Qt5 build successful!"
    echo "Binary: build/qt_64bit/qt_demo_simple"
    
    # Copy binary to build directory for easier access
    cp qt_demo_simple ../qt_demo_64bit
    echo "Binary copied to: build/qt_demo_64bit"
else
    echo "64-bit Qt5 build failed!"
    exit 1
fi

cd ..