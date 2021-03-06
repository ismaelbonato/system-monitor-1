#-------------------------------------------------
#
# Project created by QtCreator 2016-08-08T12:24:53
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = system-monitor
TEMPLATE = app

target.path = /usr/bin

desktop.path = /usr/share/applications
desktop.files += system-monitor.desktop

INSTALLS += target desktop

#icon.path = utilities-system-monitor
#icon.files += system-monitor.png

VERSION_MAJOR = 0
VERSION_MINOR = 0
VERSION_BUILD = 90

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
       "VERSION_MINOR=$$VERSION_MINOR"\
       "VERSION_BUILD=$$VERSION_BUILD"

#Target version
VERSION = $${VERSION_MAJOR}.$${VERSION_MINOR}.$${VERSION_BUILD}

SOURCES += main.cpp\
        mainwindow.cpp \
    processinformationworker.cpp \
    workerthread.cpp \
    resourcesworker.cpp \
    filesystemworker.cpp \
    processpropertiesdialogue.cpp \
    processtools.cpp \
    aboutdialogue.cpp \
    qcustomplot.cpp \
    cputools.cpp \
    preferencesdialogue.cpp \
    memoryconverter.cpp \
    colourhelper.cpp

HEADERS  += mainwindow.h \
    processinformationworker.h \
    tablenumberitem.h \
    workerthread.h \
    resourcesworker.h \
    tablememoryitem.h \
    filesystemworker.h \
    processpropertiesdialogue.h \
    processtools.h \
    aboutdialogue.h \
    qcustomplot.h \
    cputools.h \
    preferencesdialogue.h \
    hashqstring.h \
    memoryconverter.h \
    colourhelper.h \
    splinefunction.h

FORMS    += mainwindow.ui \
    processpropertiesdialogue.ui \
    aboutdialogue.ui \
    preferencesdialogue.ui

QMAKE_CXXFLAGS += -std=c++14 -Wall $$system(pkg-config --cflags eigen3)
LIBS += -L"libprocps" -lprocps -lstdc++fs

DISTFILES += \
    system-monitor.desktop
