#-------------------------------------------------
#
# Project created by QtCreator 2015-03-26T08:12:38
#
#-------------------------------------------------
greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}
QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCP_COM
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mytcpserver.cpp\
    mytcpclient.cpp

HEADERS  += mainwindow.h \
    mytcpserver.h\
    mytcpclient.h

FORMS    += mainwindow.ui
