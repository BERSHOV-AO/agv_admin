QT       += core gui sql concurrent

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
    entities_sources/toitem.cpp \
    main_window_tables_sources/mainwindow.cpp \
    main_window_tables_sources/userstableshowandediting.cpp \
    main_window_tables_sources/modelredactordialog.cpp \
    main_window_tables_sources/tablelogagvshow.cpp \
    main_window_tables_sources/addagvwidget.cpp \
    agv_sources/agvadddialog.cpp \
    agv_sources/agveditdialog.cpp \
    agv_sources/tableagvshow.cpp \
    user_sources/useradddialog.cpp \
    user_sources/usereditdialog.cpp \
    custommessagebox.cpp \
    database.cpp \   
    main.cpp \  
    modeladddialog.cpp \         
    tableselectedmodelshowdialog.cpp \
    tabletooneagvshowdialog.cpp \
    toaddfrommodeldialog.cpp \
    toeditdialog.cpp


HEADERS += \
    entities_headers/useritem.h \
    entities_headers/agvitem.h \
    entities_headers/agvtoitem.h \
    entities_headers/logitem.h \
    entities_headers/modelagvitem.h \
    entities_headers/toitem.h \
    main_window_tables_headers/mainwindow.h \
    main_window_tables_headers/userstableshowandediting.h \
    main_window_tables_headers/modelredactordialog.h \
    main_window_tables_headers/tablelogagvshow.h \
    main_window_tables_headers/addagvwidget.h \
    agv_headers/agvadddialog.h \
    agv_headers/agveditdialog.h \
    agv_headers/tableagvshow.h \
    user_headers/useradddialog.h \
    user_headers/usereditdialog.h \
    tabletooneagvshowdialog.h \
    custommessagebox.h \
    database.h \     
    modeladddialog.h \        
    tableselectedmodelshowdialog.h \   
    toaddfrommodeldialog.h \
    toeditdialog.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
