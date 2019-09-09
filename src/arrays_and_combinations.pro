TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        data_input_output.cpp \
        letter.cpp \
        letter_helpers.cpp \
        main.cpp

HEADERS += \
    combinator.h \
    data_input_output.h \
    letter.h \
    letter_helpers.h
