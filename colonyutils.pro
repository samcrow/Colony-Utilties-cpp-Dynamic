#-------------------------------------------------
#
# Project created by QtCreator 2012-08-13T11:15:39
#
#-------------------------------------------------

QT       -= gui
QT += core

TARGET = colonyutils
TEMPLATE = lib

DEFINES += COLONYUTILS_LIBRARY

SOURCES += \
	colony.cpp

HEADERS += \
	colony.hpp \
	colonyutils_global.hpp

symbian {
	MMP_RULES += EXPORTUNFROZEN
	TARGET.UID3 = 0xE9A5209A
	TARGET.CAPABILITY =
	TARGET.EPOCALLOWDLLDATA = 1
	addFiles.sources = colonyutils.dll
	addFiles.path = !:/sys/bin
	DEPLOYMENT += addFiles
}

unix:!symbian {
	maemo5 {
		target.path = /opt/usr/lib
	} else {
		target.path = /usr/lib
	}
	INSTALLS += target
}
