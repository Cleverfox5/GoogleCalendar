QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcalendar.cpp \
    calendarlist.cpp \
    calendarwindow.cpp \
    createcalendardialog.cpp \
    creatingevents.cpp \
    inputdatadialog.cpp \
    loginform.cpp \
    main.cpp \
    mainwindow.cpp \
    weekwindow.cpp

HEADERS += \
    addcalendar.h \
    calendarlist.h \
    calendarwindow.h \
    createcalendardialog.h \
    creatingevents.h \
    inputdatadialog.h \
    loginform.h \
    mainwindow.h \
    weekwindow.h

FORMS += \
    addcalendar.ui \
    calendarlist.ui \
    calendarwindow.ui \
    createcalendardialog.ui \
    creatingevents.ui \
    inputdatadialog.ui \
    loginform.ui \
    mainwindow.ui \
    weekwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
