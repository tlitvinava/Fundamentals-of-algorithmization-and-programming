QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mytree.cpp \
    tree.cpp \
    treenode.cpp

HEADERS += \
    mainwindow.h \
    mytree.h \
    tree.h \
    treenode.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    Task_2.pro

DISTFILES += \
    .gitignore \
    Lab7Task2.pro.user \
    Task_2.pro.user \
    Task_2.pro.user.c0f1449
