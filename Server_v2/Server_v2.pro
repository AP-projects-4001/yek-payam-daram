QT       += core gui

QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    main.cpp \
    message.cpp \
    myserver.cpp \
    mythread.cpp \
    date.cpp \
    chatroom_abs.cpp \
    datetime.cpp \
    private_chat.cpp \
    timekhodam.cpp

HEADERS += \
    account.h \
    chatroom_abs.h \
    message.h \
    myserver.h \
    mythread.h \
    date.h \
    datetime.h \
    private_chat.h \
    timekhodam.h

FORMS += \
    myserver.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
