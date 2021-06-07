#-------------------------------------------------
#
# Project created by QtCreator 2018-11-11T00:48:27
#
#-------------------------------------------------

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EQFilterGroup
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    AudioPlayer.cpp \
    AudioBufferDevice.cpp \
    EQFilterGroup.cpp \
    widget.cpp \
    bandpassFilter/fir1_data.cpp \
    bandpassFilter/fir1_emxutil.cpp \
    bandpassFilter/fir1_initialize.cpp \
    bandpassFilter/fir1_rtwutil.cpp \
    bandpassFilter/fir1_terminate.cpp \
    bandpassFilter/fir1.cpp \
    bandpassFilter/firls.cpp \
    bandpassFilter/mldivide.cpp \
    bandpassFilter/rt_nonfinite.cpp \
    bandpassFilter/rtGetInf.cpp \
    bandpassFilter/rtGetNaN.cpp \
    bandpassFilter/string1.cpp \
    bandpassFilter/validatestring.cpp \
    bandpassFilter/xnrm2.cpp \
    bandpassFilter/xzgeqp3.cpp


HEADERS += \
    AudioPlayer.h \
    AudioBufferDevice.h \
    EQFilterGroup.h \
    fdacoefs.h \
    widget.h \
    bandpassFilter/fir1_data.h \
    bandpassFilter/fir1_emxutil.h \
    bandpassFilter/fir1_initialize.h \
    bandpassFilter/fir1_rtwutil.h \
    bandpassFilter/fir1_terminate.h \
    bandpassFilter/fir1_types.h \
    bandpassFilter/fir1.h \
    bandpassFilter/firls.h \
    bandpassFilter/mldivide.h \
    bandpassFilter/rt_nonfinite.h \
    bandpassFilter/rtGetInf.h \
    bandpassFilter/rtGetNaN.h \
    bandpassFilter/rtwtypes.h \
    bandpassFilter/string1.h \
    bandpassFilter/tmwtypes.h \
    bandpassFilter/validatestring.h \
    bandpassFilter/xnrm2.h \
    bandpassFilter/xzgeqp3.h


FORMS += \
    widget.ui


INCLUDEPATH += $$PWD/bandpassFilter
DEPENDPATH += $$PWD/bandpassFilter

