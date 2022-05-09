#ifndef SEQUENCEDIAGRAMWINDOW_H
#define SEQUENCEDIAGRAMWINDOW_H

#include <QMainWindow>
#include "./Models/seqdscene.h"
#include "./Models/classesmodel.h"
#include "./Models/instancesmodel.h"
#include "./Models/methodmodel.h"
#include "./SeqDiagItems/instanceitem.h"
#include <QVector>
#include "./SeqDiagItems/userinstance.h"
#include "./SeqDiagItems/instanceline.h"
#include "../Entities/SeqDiagram/sequencemodel.h"
#include "mainwindow.h"
#include <QMessageBox>

namespace Ui {
class SequenceDiagramWindow;
}

class MainWindow;

class SequenceDiagramWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void CreateInstance();
    void DeleteInstance();
    void ProlongueLine();
    void ShortenLine();
    void ChangeVisibility();
    void AddInitialBlock();
    void ProlongueBlock();
    void ShortenBlock();
    void SwitchSyncAsync();
    void ReturnMessage();
    void SetMethod();
    void SaveFile();
    void OpenFile();

public:
    explicit SequenceDiagramWindow(SequenceModel *sequenceModel, MainWindow *mainWindow, QWidget *parent = 0);
    ~SequenceDiagramWindow();
    void InitScene(MethodModel*mm);
    void RefreshModel();

private:
    Ui::SequenceDiagramWindow *ui;
    SeqDScene *scene;
    ClassesModel *cm;
    InstancesModel *im;
    MethodModel*mm;

    MainWindow *mainWindow;
    SequenceModel *sequenceModel;

    UserInstance*user;
    InstanceLine*user_line;
    QVector<InstanceItem*> instanceItems;

};

#endif // SEQUENCEDIAGRAMWINDOW_H
