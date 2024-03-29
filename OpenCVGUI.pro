#-------------------------------------------------
#
# Project created by QtCreator 2017-03-14T14:26:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVGUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        qcwidget.cpp \
    opencvworker.cpp \
    imgproc.cpp



HEADERS  += qcwidget.h \
    opencvworker.h \
    imgproc.h

FORMS    += qcwidget.ui \
    imgproc.ui




macx: LIBS += -L$$PWD/../../../../usr/local/Cellar/opencv3/HEAD-a2fed4c/lib/ -lopencv_core.3.2.0
macx: LIBS += -L$$PWD/../../../../usr/local/Cellar/opencv3/HEAD-a2fed4c/lib/ -lopencv_highgui.3.2.0
macx: LIBS += -L$$PWD/../../../../usr/local/Cellar/opencv3/HEAD-a2fed4c/lib/ -lopencv_videoio.3.2.0
macx: LIBS += -L$$PWD/../../../../usr/local/Cellar/opencv3/HEAD-a2fed4c/lib/ -lopencv_imgproc.3.2.0

INCLUDEPATH += $$PWD/../../../../usr/local/Cellar/opencv3/HEAD-a2fed4c/include
DEPENDPATH += $$PWD/../../../../usr/local/Cellar/opencv3/HEAD-a2fed4c/include
