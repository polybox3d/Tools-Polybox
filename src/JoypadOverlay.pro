#-------------------------------------------------
#
# Project created by QtCreator 2013-10-22T18:25:20
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = JoypadOverlay
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    ActionButton.cpp \
    JoypadWidget.cpp \
    Action.cpp \
    ConsoleWidget.cpp \
    ControleWidget.cpp \
    DialogAddAction.cpp

HEADERS  += MainWindow.h \
    ActionButton.h \
    JoypadWidget.h \
    Action.h \
    ConsoleWidget.h \
    ControleWidget.h \
    DialogAddAction.h

FORMS    += MainWindow.ui \
    JoypadWidget.ui \
    ConsoleWidget.ui \
    ControleWidget.ui \
    DialogAddAction.ui

RESOURCES += \
    ressources.qrc
