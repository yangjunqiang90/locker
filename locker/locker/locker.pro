#-------------------------------------------------
#
# Project created by QtCreator 2016-04-16T20:09:08
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = locker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    passworddialog.cpp \
    settingdialog.cpp \
    info.cpp \
    timedialog.cpp \
    voicepassworddialog.cpp \
    voicehintdialog.cpp \
    MyLock.cpp

HEADERS  += mainwindow.h \
    passworddialog.h \
    settingdialog.h \
    info.h \
    timedialog.h \
    voicehintdialog.h \
    voicepassworddialog.h \
    MyLock.h

FORMS    += mainwindow.ui \
    passworddialog.ui \
    settingdialog.ui \
    timedialog.ui \
    voicepassworddialog.ui \
    voicehintdialog.ui

RESOURCES += \
    image.qrc
#LIBS += -lwiringPi
