TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Server.c \
    process_list.c

HEADERS += \
    server.h \
    process_list.h
