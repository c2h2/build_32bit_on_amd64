QT += core widgets
CONFIG += c++11

TARGET = qt_demo
TEMPLATE = app

SOURCES += qt_demo.cpp

# Ensure we use the correct Qt version
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets