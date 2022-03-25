QT      += core gui
QT      += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    game.cpp \
    field.cpp \
    network/Network.cpp \
    network/NetworkTcpClient.cpp \
    network/NetworkTcpServer.cpp \
    network/dataRecievedEvent.cpp \
    player.cpp \
    cell.cpp \
    cell_gui.cpp \
    fivewins.cpp \
    menu.cpp

HEADERS += \
    game.h \
    field.h \
    network/Network.h \
    network/NetworkTcpClient.h \
    network/NetworkTcpServer.h \
    network/dataRecievedEvent.h \
    player.h \
    cell.h \
    cell_gui.h \
    fivewins.h \
    menu.h

FORMS += \
    fivewins.ui \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
