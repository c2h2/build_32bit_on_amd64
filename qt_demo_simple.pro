QT += core widgets
CONFIG += c++11

TARGET = qt_demo_simple
TEMPLATE = app

SOURCES += qt_demo_simple.cpp

# Ensure we use the correct Qt version
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets