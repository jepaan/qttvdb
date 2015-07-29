TEMPLATE = lib

CONFIG += staticlib

TARGET = qttvdb

QT += xml

HEADERS += qttvdb.h qttvdb_export.h
SOURCES += episode.cpp mirrors.cpp show.cpp banner.cpp

DEFINES += QTTVDB_EXPORT=""
