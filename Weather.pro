QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Weather
TEMPLATE = app

INCLUDEPATH += ./include
HEADERS += \
    include/addlocationdialog.h \
    include/basedetail.h \
    include/collectwidget.h \
    include/contentwidget.h \
    include/currentdetail.h \
    include/dailydetail.h \
    include/dailywidget.h \
    include/forcastwidget.h \
    include/horizonalslider.h \
    include/hourlydetail.h \
    include/hourlywidget.h \
    include/loadingwidget.h \
    include/locationedit.h \
    include/locationwidget.h \
    include/mainpage.h \
    include/settingwidget.h \
    include/titlewidget.h \
    include/unitType.h \
    include/weather.h

SOURCES += \
    src/addlocationdialog.cpp \
    src/basedetail.cpp \
    src/collectwidget.cpp \
    src/contentwidget.cpp \
    src/currentdetail.cpp \
    src/dailydetail.cpp \
    src/dailywidget.cpp \
    src/forcastwidget.cpp \
    src/horizonalslider.cpp \
    src/hourlydetail.cpp \
    src/hourlywidget.cpp \
    src/loadingwidget.cpp \
    src/locationedit.cpp \
    src/locationwidget.cpp \
    src/main.cpp \
    src/mainpage.cpp \
    src/settingwidget.cpp \
    src/titlewidget.cpp \
    src/weather.cpp

FORMS += \
    ui/forcastwidget.ui \
    ui/loadingwidget.ui \
    ui/locationwidget.ui \
    ui/mainpage.ui \
    ui/settingwidget.ui \
    ui/weather.ui

RESOURCES += \
    images.qrc \
    cityList.qrc

LIBS += -lqjson
