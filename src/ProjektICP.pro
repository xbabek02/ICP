QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
TEMPLATE = app
TARGET = ProjektICP

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ClassDiagramCommands/addclassattributecommand.cpp \
    ClassDiagramCommands/classmovecommand.cpp \
    ClassDiagramCommands/createclasscommand.cpp \
    ClassDiagramCommands/createconnectioncommand.cpp \
    ClassDiagramCommands/createsingletoncommand.cpp \
    ClsDiagItems/classdiagramitem.cpp \
    ClsDiagItems/classitemhead.cpp \
    ClsDiagItems/connection.cpp \
    Screens/mainwindow.cpp \
    ClsDiagItems/selectline.cpp \
    ClsDiagItems/singletonconnection.cpp \
    ClsDiagItems/textitem.cpp\
    ClsDiagItems/textstateitem.cpp \
\
    Screens/sequencediagramwindow.cpp \
    Models/classesmodel.cpp \
    Models/seqdscene.cpp \
    SeqDiagItems/instanceitem.cpp \
    SeqDiagItems/userinstance.cpp \
    Models/instancesmodel.cpp \
    SeqDiagItems/messageitem.cpp \
    SeqDiagItems/rectangle.cpp \
\
    main.cpp \
\
    Entities/AttributeEntity.cpp \
    Entities/DiagramEntity.cpp \
    Entities/Model.cpp \
    Entities/ModelObject.cpp \
    Entities/SeqDiagram/blockentity.cpp \
    Entities/SeqDiagram/instanceentity.cpp \
    Entities/SeqDiagram/message.cpp \
    Entities/SeqDiagram/sequencemodel.cpp \
    IO/ioxmlparsing.cpp \
    Common/enums.cpp \
    Entities/RelationEntity.cpp \
    Models/methodmodel.cpp \
    SeqDiagItems/textitem_instance.cpp \
    SeqDiagItems/id.cpp

HEADERS += \
    Screens/mainwindow.h \
    ClassDiagramCommands/addclassattributecommand.h \
    ClassDiagramCommands/classmovecommand.h \
    ClassDiagramCommands/createclasscommand.h \
    ClassDiagramCommands/createconnectioncommand.h \
    ClassDiagramCommands/createsingletoncommand.h \
    ClsDiagItems/classdiagramitem.h \
    ClsDiagItems/classitemhead.h \
    ClsDiagItems/connection.h \
    ClsDiagItems/selectline.h \
    ClsDiagItems/singletonconnection.h \
    ClsDiagItems/textitem.h\
    ClsDiagItems/textstateitem.h \
\
    Screens/sequencediagramwindow.h \
    Models/classesmodel.h \
    Models/seqdscene.h \
    SeqDiagItems/instanceitem.h \
    SeqDiagItems/userinstance.h \
    Models/instancesmodel.h \
    SeqDiagItems/messageitem.h \
    SeqDiagItems/rectangle.h \
\
    Entities/AttributeEntity.h \
    Entities/DiagramEntity.h \
    Entities/Model.h \
    Entities/ModelObject.h \
    Entities/SeqDiagram/blockentity.h \
    Entities/SeqDiagram/instanceentity.h \
    Entities/SeqDiagram/message.h \
    Entities/SeqDiagram/sequencemodel.h \
    Common/enums.h \    
    Entities/RelationEntity.h \
    Models/methodmodel.h \
    SeqDiagItems/textitem_instance.h \
    SeqDiagItems/idcls.h

FORMS += \
    Screens/mainwindow.ui \
    Screens/sequencediagramwindow.ui

QMAKE_CXXFLAGS += -std=c++0x

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
