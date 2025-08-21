#!/bin/bash

echo "Building Qt5 demo for native 64-bit architecture..."

# Create build directory
mkdir -p build_64bit
cd build_64bit

# Use native qmake to configure for 64-bit build
if command -v qmake-qt5 >/dev/null 2>&1; then
    echo "Using qmake-qt5..."
    qmake-qt5 ../qt_demo_simple.pro
else
    echo "Using qmake..."
    qmake ../qt_demo_simple.pro
fi

# Build with make
if make; then
    echo "64-bit Qt5 build successful!"
    echo "Binary: build_64bit/qt_demo"
    
    # Copy binary to root directory for easier access
    cp qt_demo_simple ../qt_demo_64bit
    echo "Binary copied to: qt_demo_64bit"
else
    echo "64-bit Qt5 build failed!"
    exit 1
fi

cd ..