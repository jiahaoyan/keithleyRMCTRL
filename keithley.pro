#-------------------------------------------------
#
# Project created by QtCreator 2015-10-09T11:12:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = keithley
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialdialog.cpp \
    aboutdialog.cpp \
    modeldialog.cpp \
    include/qextserialbase.cpp \
    include/qextserialport.cpp \
    include/win_qextserialport.cpp \
    biasdialog.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    serialdialog.h \
    aboutdialog.h \
    modeldialog.h \
    include/qextserialbase.h \
    include/qextserialport.h \
    include/win_qextserialport.h \
    biasdialog.h \
    mythread.h

FORMS    += mainwindow.ui \
    serialdialog.ui \
    aboutdialog.ui \
    modeldialog.ui \
    biasdialog.ui
