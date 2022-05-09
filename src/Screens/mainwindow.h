/**
 * @file mainwindow.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Main window for the class diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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

class SequenceDiagramWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QList<ClassDiagramItem*> *GetItems();

private slots:
    /**
     * @brief AddClassButton creates new class
     */
    void AddClassButton();

    /**
     * @brief AddRowButton adds new row (attribute/method) into the class
     */
    void AddRowButton();

    /**
     * @brief RemoveRowButton removes row from the class
     */
    void RemoveRowButton();

    /**
     * @brief AddLine creates relation between two classes
     */
    void AddLine();

    /**
     * @brief MethodDownButton adds one attrbute and removes one method from the class
     */
    void MethodDownButton();

    /**
     * @brief MethodUpButton adds one method and removes one attribute from the object
     */
    void MethodUpButton();

    /**
     * @brief RotateLineButton rotates relation line
     */
    void RotateLineButton();

    /**
     * @brief ChangeLineButton cheges type of the line
     */
    void ChangeLineButton();

    /**
     * @brief ZoomIn
     */
    void ZoomIn();

    /**
     * @brief ZoomOut
     */
    void ZoomOut();

    /**
     * @brief DeleteNodeButton deletes selected objects
     */
    void DeleteNodeButton();

    /**
     * @brief OpenFileButton load class diagram from the file
     */
    void OpenFileButton();

    /**
     * @brief SaveFileButton saves class diagram from the class
     */
    void SaveFileButton();

    /**
     * @brief PlusClassWidth increases width of the class
     */
    void PlusClassWidth();

    /**
     * @brief MinusClassWidth decreases class width
     */
    void MinusClassWidth();

    /**
     * @brief PlusLineDistance adds distance from the center of the singleton line
     */
    void PlusLineDistance();

    /**
     * @brief MinusLineDistance decreases singleton line distance from the center
     */
    void MinusLineDistance();

    /**
     * @brief CreateSequence creates new sequence diagram
     */
    void CreateSequence();

    /**
     * @brief UndoButton undo operation
     */
    void UndoButton();

signals:
    /**
     * @brief itemsChanged
     */
    void itemsChanged();

private:
    /**
     * @brief ui
     */
    Ui::MainWindow *ui;

    /**
     * @brief scene
     */
    QGraphicsScene *scene;

    /**
     * @brief items
     */
    QList<ClassDiagramItem*> items;

    /**
     * @brief connections
     */
    QList<Connection*> connections;

    /**
     * @brief singletons
     */
    QList<SingletonConnection*> singletons;

    /**
     * @brief sequenceDiagrams
     */
    QList<SequenceDiagramWindow*> sequenceDiagrams;

    /**
     * @brief RefreshSequenceDiagrams refreshe sequence diagram screen
     */
    void RefreshSequenceDiagrams();

    /**
     * @brief AddSingletonLine adds singleton line
     */
    void AddSingletonLine();

    /**
     * @brief mainModel
     */
    Model *mainModel;

    /**
     * @brief undoStack
     */
    QUndoStack *undoStack = nullptr;
};

#endif // MAINWINDOW_H
