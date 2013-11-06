#-------------------------------------------------
#
# Project created by QtCreator 2013-06-24T11:54:27
#
#-------------------------------------------------

QT       += core testlib

QT       -= gui

TARGET = libqkwp2000-test
CONFIG   += console
CONFIG   -= app_bundle
CONFIG	+= debug
TEMPLATE = app

CLEANDIRS = "debug release"
CLEANFILES += $$TARGET
QMAKE_CLEAN += -r $$CLEANDIRS $$CLEANFILES


SOURCES += main.cpp \
    test_libqkwp2000.cpp

HEADERS += \
    test_libqkwp2000.h

CONFIG(debug, debug|release) {
	LIBS += -L$$PWD/../src/debug/ -lqkwp2000
	QMAKE_POST_LINK = $$PWD/$${TARGET}
} else {
	LIBS += -L$$PWD/../src/release/ -lqkwp2000
	QMAKE_POST_LINK = $$PWD/$${TARGET}
}

INCLUDEPATH += $$PWD/../src/
DEPENDPATH += $$PWD/../src/
