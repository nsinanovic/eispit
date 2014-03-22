#-------------------------------------------------
#
# Project created by QtCreator 2014-02-01T20:31:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCvApp
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += C:\\Users\\Nusreta\\Desktop\\opencv\\build\\include
LIBS += -LC:\\Users\\Nusreta\\Desktop\\builds\\lib \
    -lopencv_core231 \
    -lopencv_highgui231 \
    -lopencv_imgproc231 \
    -lopencv_features2d231 \
    -lopencv_calib3d231
