TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    Nos_fichiers/game.cpp \
    Nos_fichiers/gridmanagement.cpp \
    main.cpp \
    Nos_fichiers/config.cpp \
    Nos_fichiers/gamemod.cpp \
    Nos_fichiers/bonus.cpp

DISTFILES += \
    Nos_fichiers/config/config.yaml \
    Nos_fichiers/lang/fr.yaml \
    Nos_fichiers/lang/en.yaml

HEADERS += \
    Nos_fichiers/game.h \
    Nos_fichiers/gridmanagement.h \
    Nos_fichiers/type.h \
    Nos_fichiers/config.h \
    Nos_fichiers/gamemod.h \
    Nos_fichiers/bonus.h
