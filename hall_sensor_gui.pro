#-------------------------------------------------
#
# Project created by QtCreator 2021-01-08T14:32:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = hall_sensor_gui
#TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

INCLUDEPATH += ./headers

SOURCES += \
    button.cpp \
    dialog.cpp \
    hall_sensor.cpp \
    led_kit.cpp \
    led_state.cpp \
    main.cpp \
    mainwindow.cpp \
    speedometer.cpp \
    thread_inc.cpp \
    unitchanger.cpp \
    value.cpp \
    value_double.cpp

HEADERS += \
    button.h \
    dialog.h \
    headers/buzzer.h \
    headers/element.h \
    headers/hall_sensor.h \
    headers/led.h \
    headers/led_kit.h \
    headers/leds_state.h \
    headers/mainwindow.h \
    headers/thread.h \
    headers/thread_inc.h \
    headers/timer.h \
    headers/speedometer.h \
    headers/unitchanger.h \
    value.h \
    value_double.h

LIBS += -L/usr/local/lib -lwiringPi
FORMS += \
        dialog.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
