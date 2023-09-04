QT       += core gui
QT += axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    coordinate.cpp \
    main.cpp \
    mainwindow.cpp \
    mytime.cpp \
    mywidget1.cpp \
    mywidget2.cpp \
    mywidget4.cpp \
    mywidget5.cpp \
    mywidget6.cpp \
    mywidget7.cpp \
    road.cpp

HEADERS += \
    coordinate.h \
    mainwindow.h \
    mytime.h \
    mywidget1.h \
    mywidget2.h \
    mywidget4.h \
    mywidget5.h \
    mywidget6.h \
    mywidget7.h \
    road.h

FORMS += \
    mainwindow.ui \
    mywidget1.ui \
    mywidget2.ui \
    mywidget4.ui \
    mywidget5.ui \
    mywidget6.ui \
    mywidget7.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
