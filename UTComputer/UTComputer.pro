#-------------------------------------------------
#
# Project created by QtCreator 2016-06-07T16:40:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UTComputer
TEMPLATE = app


SOURCES += main.cpp \
	computer.cpp \
	Controller.cpp \
	Literal.cpp \
	LiteralFactory.cpp \
	Operator.cpp \
	qcomputer.cpp \
	Stack.cpp \
	StackMemento.cpp

HEADERS  += \
	computer.h \
	Controller.h \
	Literal.h \
	LiteralFactory.h \
	Operator.h \
	OperatorException.h \
	qcomputer.h \
	Stack.h \
	StackMemento.h

FORMS    +=

# workaround pour compiler avec msvc 2015
INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10240.0/ucrt"

LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10240.0/ucrt/x64"
