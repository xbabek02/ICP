QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    View/classdiagramitem.cpp \
    View/classitemhead.cpp \
    View/connectline.cpp \
    View/mainwindow.cpp \
    main.cpp \
\
    Entities/AttributeEntity.cpp \
    Entities/DiagramEntity.cpp \
    Entities/Model.cpp \
    Entities/ModelObject.cpp \
    Entities/RelationEntity.cpp \
    IO/ioxmlparsing.cpp

HEADERS += \
    View/classdiagramitem.h \
    View/classitemhead.h \
    View/connectline.h \
    View/mainwindow.h \
\
    Entities/AttributeEntity.h \
    Entities/DiagramEntity.h \
    Entities/Model.h \
    Entities/ModelObject.h \
    Entities/RelationEntity.h \
    Common/enums.h \ 
    IO/ioxmlparsing.h

FORMS += \
    View/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
