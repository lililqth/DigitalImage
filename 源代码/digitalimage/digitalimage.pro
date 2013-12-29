#-------------------------------------------------
#
# Project created by QtCreator 2013-09-22T16:52:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = digitalimage
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    image.cpp \
    kongjian.cpp \
    gray_map.cpp \
    getmatrix.cpp \
    showorigin.cpp \
    showcolortable.cpp \
    slider.cpp \
    HuffmanTree.cpp

HEADERS  += mainwindow.h \
    image.h \
    gray_map.h \
    getmatrix.h \
    showorigin.h \
    showcolortable.h \
    slider.h

FORMS    += mainwindow.ui \
    gray_map.ui \
    getmatrix.ui \
    showcolortable.ui \
    slider.ui
