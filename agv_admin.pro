QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    entities_sources/agvitem.cpp \
    entities_sources/agvtoitem.cpp \
    entities_sources/modelagvitem.cpp \
    entities_sources/logitem.cpp \
    entities_sources/useritem.cpp \
    addagvwidget.cpp \
    agvadddialog.cpp \
    agveditdialog.cpp \
    custommessagebox.cpp \
    database.cpp \   
    main.cpp \
    mainwindow.cpp \
    modeladddialog.cpp \   
    modelredactordialog.cpp \
    tableagvshow.cpp \
    tablelogagvshow.cpp \
    tableselectedmodelshowdialog.cpp \
    tabletooneagvshowdialog.cpp \
    toaddfrommodeldialog.cpp \
    toeditdialog.cpp \
    toitem.cpp \
    useradddialog.cpp \
    usereditdialog.cpp \   
    userstableshowandediting.cpp

HEADERS += \
    entities_headers/useritem.h \
    entities_headers/agvitem.h \
    entities_headers/agvtoitem.h \
    entities_headers/logitem.h \
    entities_headers/modelagvitem.h \
    addagvwidget.h \
    agvadddialog.h \
    agveditdialog.h \      
    custommessagebox.h \
    database.h \   
    mainwindow.h \
    modeladddialog.h \
    modelredactordialog.h \
    tableagvshow.h \
    tablelogagvshow.h \
    tableselectedmodelshowdialog.h \
    tabletooneagvshowdialog.h \
    toaddfrommodeldialog.h \
    toeditdialog.h \
    toitem.h \
    useradddialog.h \
    usereditdialog.h \   
    userstableshowandediting.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
