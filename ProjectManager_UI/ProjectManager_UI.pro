#-------------------------------------------------
#
# Project created by QtCreator 2017-08-14T17:09:18
#
#-------------------------------------------------

QT       += core gui
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectManager_UI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    college.cpp \
    people.cpp \
    project.cpp \
    schedule.cpp \
    student.cpp \
    studentTable.cpp \
    total.cpp \
    dialogsch.cpp \
    dialogschmodify.cpp \
    dialogproadd.cpp \
    dialogpeo.cpp \
    dialogtable.cpp \
    dialogtableselect.cpp

HEADERS  += mainwindow.h \
    college.h \
    people.h \
    project.h \
    schedule.h \
    student.h \
    studentTable.h \
    total.h \
    dialogsch.h \
    dialogschmodify.h \
    dialogproadd.h \
    dialogpeo.h \
    dialogtable.h \
    dialogtableselect.h

FORMS    += mainwindow.ui \
    dialogsch.ui \
    dialogschmodify.ui \
    dialogproadd.ui \
    dialogpeo.ui \
    dialogtable.ui \
    dialogtableselect.ui

DISTFILES += \
    ProjectManager_UI.pro.user
