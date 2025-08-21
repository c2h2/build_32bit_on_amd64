#!/bin/bash

echo "Building Qt5 demo manually for 32-bit architecture..."

# Clean and create build directory
rm -rf build_32bit_manual
mkdir -p build_32bit_manual
cd build_32bit_manual

echo "Compiling Qt5 demo manually..."

# Compile the source file using 64-bit headers (compatible)
i686-linux-gnu-g++ -m32 -fPIC -O2 -std=gnu++11 \
    -I/usr/include/x86_64-linux-gnu/qt5 \
    -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets \
    -I/usr/include/x86_64-linux-gnu/qt5/QtGui \
    -I/usr/include/x86_64-linux-gnu/qt5/QtCore \
    -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB \
    -c ../qt_demo_simple.cpp -o qt_demo_simple.o

if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Link with 32-bit Qt5 libraries
i686-linux-gnu-g++ -m32 -o qt_demo_simple qt_demo_simple.o \
    -L/usr/lib/i386-linux-gnu \
    -lQt5Widgets -lQt5Gui -lQt5Core \
    -lGL -lpthread

if [ $? -eq 0 ]; then
    echo "32-bit Qt5 build successful!"
    echo "Binary: build_32bit_manual/qt_demo_simple"
    
    # Copy binary to root directory for easier access
    cp qt_demo_simple ../qt_demo_32bit
    echo "Binary copied to: qt_demo_32bit"
else
    echo "32-bit Qt5 build failed!"
    exit 1
fi

cd ..