QT       += core gui
QT += network
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    alfalfa_field.cpp \
    barn.cpp \
    chicken_coop.cpp \
    client.cpp \
    cow_pasture.cpp \
    farm.cpp \
    login.cpp \
    main.cpp \
    game.cpp \
    profile.cpp \
    register_info.cpp \
    sheep_pasture.cpp \
    silo.cpp \
    store.cpp \
    time_thread.cpp \
    wheat_field.cpp

HEADERS += \
    alfalfa_field.h \
    barn.h \
    chicken_coop.h \
    client.h \
    cow_pasture.h \
    farm.h \
    game.h \
    information.h \
    login.h \
    profile.h \
    register_info.h \
    sheep_pasture.h \
    silo.h \
    store.h \
    time_thread.h \
    wheat_field.h

FORMS += \
    alfalfa_field.ui \
    barn.ui \
    chicken_coop.ui \
    cow_pasture.ui \
    farm.ui \
    game.ui \
    login.ui \
    profile.ui \
    register_info.ui \
    sheep_pasture.ui \
    silo.ui \
    store.ui \
    wheat_field.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    game_recources.qrc \
    image.qrc \
    music.qrc

DISTFILES += \
    file.json
