#-------------------------------------------------
#
# Project created by QtCreator 2019-07-11T10:57:00
#
#-------------------------------------------------
TARGET = FDPython
TEMPLATE = lib
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += link_pkgconfig
PKGCONFIG += python3

DESTDIR = ../build/lib
MAKEFILE = ../build/makefiles/$${TARGET}
OBJECTS_DIR = ../build/obj/$${TARGET}

LIBS += -L../build/lib
LIBS += -lFDScript

INCLUDEPATH += include \
    ../FDScript/include \
    ../thirdparty/pybind11/include \

SOURCES += \
    src/Interpreter.cpp \
    src/Value.cpp

HEADERS += \
    include/FDPython/Interpreter.h \
    include/FDPython/Value.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
