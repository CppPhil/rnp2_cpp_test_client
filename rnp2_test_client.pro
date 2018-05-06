#-------------------------------------------------
#
# Project created by QtCreator 2018-05-06T10:46:44
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = rnp2_test_client
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
        mainwindow.cpp \
    read_server_address_from_file.cpp \
    netstring.cpp \
    connect_message.cpp \
    disconnect_message.cpp \
    client.cpp \
    client_list_message.cpp \
    chat_message.cpp \
    read_user_name_from_file.cpp

HEADERS += \
        mainwindow.hpp \
    read_server_address_from_file.hpp \
    ports.hpp \
    netstring.hpp \
    connect_message.hpp \
    disconnect_message.hpp \
    client.hpp \
    client_list_message.hpp \
    chat_message.hpp \
    read_user_name_from_file.hpp

FORMS += \
        mainwindow.ui

DISTFILES += \
    server_address.txt \
    user_name.txt
