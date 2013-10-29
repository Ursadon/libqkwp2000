QT       -= gui

TEMPLATE = lib
DEFINES += QKWP2000_LIBRARY

CLEANDIRS = "debug release"
CLEANFILES = "libqkwp2000.so*"
QMAKE_CLEAN += -r $$CLEANDIRS $$CLEANFILES
CONFIG += debug
include(libqkwp2000.pri)

unix:!symbian {
    maemo5 {
	target.path = /opt/usr/lib
    } else {
	target.path = /usr/lib
    }
    INSTALLS += target
}

CONFIG(debug, debug|release) { 
    DESTDIR = debug
    TARGET = qkwp2000
} else { 
    DESTDIR = release
    TARGET =qkwp2000
}

win32: SONAME=dll
else:  SONAME=so

