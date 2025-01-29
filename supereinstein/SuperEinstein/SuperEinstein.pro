QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += gui
RC_FILE = myapp.rc

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Utility/Utility.cpp \
    controller.cpp \
    data.cpp \
    main.cpp \
    object/BaseElem/baseelem.cpp \
    object/BaseElem/box.cpp \
    object/personn/minibot.cpp \
    object/personn/newton.cpp \
    object/object.cpp \
    object/personn/personn.cpp \
    object/personn/player.cpp \
    object/BaseElem/floor.cpp \
    object/BaseElem/underfloor.cpp \
    view/inputview.cpp \
    view/menu.cpp \
    view/outputview.cpp \
    view/view.cpp

HEADERS += \
    Utility/Utility.h \
    controller.h \
    data.h \
    object/BaseElem/baseelem.h \
    object/BaseElem/box.h \
    object/BaseElem/floor.h \
    object/personn/minibot.h \
    object/personn/newton.h \
    object/object.h \
    object/personn/personn.h \
    object/personn/player.h \
    object/BaseElem/underfloor.h \
    view/inputview.h \
    view/menu.h \
    view/outputview.h \
    view/view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
