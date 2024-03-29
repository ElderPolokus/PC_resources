QT       += core gui
QT       += network
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    conf_connection.cpp \
    cpu.cpp \
    disk.cpp \
    main.cpp \
    pc_resources.cpp \
    ram.cpp \
    userinfo.cpp

HEADERS += \
    conf_connection.h \
    cpu.h \
    disk.h \
    pc_resources.h \
    ram.h \
    userinfo.h

FORMS += \
    conf_connection.ui \
    pc_resources.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    img/pngwing.com (1).png
