QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    book.cpp \
    explore.cpp \
    main.cpp \
    mainoperator.cpp \
    person.cpp \
    regis.cpp \
    super_explore.cpp \
    superviser_mainioeratorfor.cpp \
    widget.cpp

HEADERS += \
    book.h \
    explore.h \
    mainoperator.h \
    person.h \
    regis.h \
    super_explore.h \
    superviser_mainioeratorfor.h \
    widget.h

FORMS += \
    explore.ui \
    mainoperator.ui \
    regis.ui \
    super_explore.ui \
    superviser_mainioeratorfor.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
