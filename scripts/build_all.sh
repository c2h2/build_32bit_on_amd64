#!/bin/bash

# Change to project root directory
PROJECT_ROOT="$(dirname "$(dirname "$(realpath "$0")")")"
cd "$PROJECT_ROOT"

echo "========================================="
echo "Building All Cross-compilation Demos"
echo "========================================="

# Function to check if command succeeded
check_build() {
    if [ $? -eq 0 ]; then
        echo "✅ $1 build successful"
    else
        echo "❌ $1 build failed"
        FAILED_BUILDS="$FAILED_BUILDS $1"
    fi
}

FAILED_BUILDS=""

echo ""
echo "1. Building C Language Demos..."
echo "--------------------------------"

# Build C 32-bit
echo "Building C 32-bit..."
./scripts/build_64bit_to_32bit.sh
check_build "C 32-bit"

# Build C 64-bit
echo "Building C 64-bit..."
./scripts/build_native.sh
check_build "C 64-bit"

echo ""
echo "2. Building C++ Language Demos..."
echo "----------------------------------"

# Build C++ 32-bit
echo "Building C++ 32-bit..."
./scripts/build_cpp_32bit.sh
check_build "C++ 32-bit"

# Build C++ 64-bit
echo "Building C++ 64-bit..."
./scripts/build_cpp_native.sh
check_build "C++ 64-bit"

echo ""
echo "3. Building Qt5 Demos..."
echo "-------------------------"

# Build Qt5 32-bit
echo "Building Qt5 32-bit..."
./scripts/build_qt_32bit.sh
check_build "Qt5 32-bit"

# Build Qt5 64-bit
echo "Building Qt5 64-bit..."
./scripts/build_qt_native.sh
check_build "Qt5 64-bit"

echo ""
echo "========================================="
echo "Build Summary"
echo "========================================="

if [ -z "$FAILED_BUILDS" ]; then
    echo "🎉 All builds completed successfully!"
    echo ""
    echo "Generated binaries:"
    echo "  C Language:"
    echo "    - build/test_length_32bit (32-bit)"
    echo "    - build/test_length_64bit (64-bit)"
    echo "  C++ Language:"
    echo "    - build/demo_32bit (32-bit)"
    echo "    - build/demo_64bit (64-bit)"
    echo "  Qt5 GUI:"
    echo "    - build/qt_demo_32bit (32-bit)"
    echo "    - build/qt_demo_64bit (64-bit)"
    echo ""
    echo "Verification commands:"
    echo "  file build/test_length_32bit build/test_length_64bit"
    echo "  file build/demo_32bit build/demo_64bit"
    echo "  file build/qt_demo_32bit build/qt_demo_64bit"
else
    echo "⚠️  Some builds failed:$FAILED_BUILDS"
    echo ""
    echo "Please check the error messages above and ensure all dependencies are installed."
fi

echo "========================================="