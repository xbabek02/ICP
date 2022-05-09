#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include "./ClsDiagItems/classdiagramitem.h"
#include <typeinfo>
#include "./ClsDiagItems/connection.h"
#include "./ClsDiagItems/textstateitem.h"
#include "./ClsDiagItems/singletonconnection.h"
#include "../Entities/Model.h"
#include "../Entities/RelationEntity.h"
#include "../ClassDiagramCommands/createclasscommand.h"
#include "../ClassDiagramCommands/createconnectioncommand.h"
#include "../ClassDiagramCommands/createsingletoncommand.h"
#include <QFileDialog>
#include <QUndoStack>
#include "../ClassDiagramCommands/classmovecommand.h"
#include "../ClassDiagramCommands/addclassattributecommand.h"
#include "../ClassDiagramCommands/deleteclasscommand.h"
#include "sequencediagramwindow.h"
#include "Entities/SeqDiagram/sequencemodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<ClassDiagramItem*> *GetItems();

private slots:
    void AddClassButton();
    void AddRowButton();
    void RemoveRowButton();
    void AddLine();
    void MethodDownButton();
    void MethodUpButton();
    void RotateLineButton();
    void ChangeLineButton();
    void ZoomIn();
    void ZoomOut();
    void DeleteNodeButton();
    void OpenFileButton();
    void SaveFileButton();
    void PlusClassWidth();
    void MinusClassWidth();
    void PlusLineDistance();
    void MinusLineDistance();
    void CreateSequence();
    void UndoButton();

signals:
    void itemsChanged();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QList<ClassDiagramItem*> items;
    QList<Connection*> connections;
    QList<SingletonConnection*> singletons;
    void AddSingletonLine();
    Model *mainModel;
    QUndoStack *undoStack = nullptr;
};

#endif // MAINWINDOW_H
