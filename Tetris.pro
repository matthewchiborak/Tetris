QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    background_renderer.cpp \
    block.cpp \
    blockfactory.cpp \
    blockrandomfactory.cpp \
    boardmodel.cpp \
    gamecontroller.cpp \
    gamestate.cpp \
    inputcommand.cpp \
    inputcommandfactory.cpp \
    main.cpp \
    mainwindow.cpp \
    openglwindow.cpp \
    sidebar.cpp

HEADERS += \
    background_renderer.h \
    block.h \
    blockfactory.h \
    blockrandomfactory.h \
    boardmodel.h \
    gamecontroller.h \
    gamestate.h \
    inputcommand.h \
    inputcommandfactory.h \
    mainwindow.h \
    openglwindow.h \
    sidebar.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    TetrisPieces.png
