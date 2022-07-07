QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    contact.cpp \
    date.cpp \
    datetime.cpp \
    group_pro.cpp \
    log_in.cpp \
    main.cpp \
    mainpage.cpp \
    mainwindow.cpp \
    nameofgroup.cpp \
    profile.cpp \
    sign_in.cpp \
    timekhodam.cpp \
    typechatwin.cpp \
    usersettings.cpp

HEADERS += \
    account.h \
    contact.h \
    date.h \
    datetime.h \
    group_pro.h \
    log_in.h \
    mainpage.h \
    mainwindow.h \
    nameofgroup.h \
    profile.h \
    sign_in.h \
    timekhodam.h \
    typechatwin.h \
    usersettings.h

FORMS += \
    contact.ui \
    group_pro.ui \
    log_in.ui \
    mainpage.ui \
    mainwindow.ui \
    nameofgroup.ui \
    profile.ui \
    sign_in.ui \
    typechatwin.ui \
    usersettings.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
