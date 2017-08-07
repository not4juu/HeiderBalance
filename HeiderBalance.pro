#-------------------------------------------------
#
# Project created by Sebastia Kaluzny 2016-09-19T20:20:33
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HeiderBalance
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    glwidget.cpp \
    generator.cpp \
    rk4.cpp \
    trajectoriesdialog.cpp \
    point3d.cpp \
    stere.cpp \
    statisticspointsetupdialog.cpp \
    statoutput.cpp \
    statstereoutput.cpp \
    colorproperties.cpp \
    plane.cpp \
    planesdialog.cpp \
    aboutdialog.cpp \
    sterecolorsdialog.cpp

HEADERS  += mainwindow.h \
    glwidget.h \
    generator.h \
    rk4.h \
    trajectoriesdialog.h \
    point3d.h \
    stere.h \
    statisticspointsetupdialog.h \
    statoutput.h \
    statstereoutput.h \
    colorproperties.h \
    plane.h \
    planesdialog.h \
    aboutdialog.h \
    sterecolorsdialog.h

FORMS    += mainwindow.ui \
    trajectoriesdialog.ui \
    statisticspointsetupdialog.ui \
    planesdialog.ui \
    aboutdialog.ui \
    sterecolorsdialog.ui

LIBS += -lglut -lGLU
RESOURCES = application.qrc
