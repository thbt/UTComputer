QT += widgets

QMAKE_CXXFLAGS = -std=c++11
QMAKE_LFLAGS = -std=c++11

SOURCES += \
    main.cpp \
    qcomputer.cpp \
    Controller.cpp \
    Literal.cpp \
    LiteralFactory.cpp \
    Operator.cpp \
    Stack.cpp \
    StackMemento.cpp

HEADERS += \
    qcomputer.h \
    Controller.h \
    Literal.h \
    LiteralFactory.h \
    Operator.h \
    OperatorException.h \
    Stack.h \
    StackMemento.h
