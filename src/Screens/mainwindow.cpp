#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "./ClsDiagItems/classitemhead.h"
#include "./ClsDiagItems/textitem.h"
#include <string>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    undoStack = new QUndoStack(this);
    ui->setupUi(this);

    //connects button functions to buttons
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(AddRowButton()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(RemoveRowButton()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(AddClassButton()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(AddLine()));
    connect(ui->pushButton_5, SIGNAL(clicked(bool)), this, SLOT(MethodUpButton()));
    connect(ui->pushButton_6, SIGNAL(clicked(bool)), this, SLOT(MethodDownButton()));
    connect(ui->pushButton_7, SIGNAL(clicked(bool)), this, SLOT(RotateLineButton()));
    connect(ui->pushButton_8, SIGNAL(clicked(bool)), this, SLOT(ChangeLineButton()));
    connect(ui->pushButton_9, SIGNAL(clicked(bool)), this, SLOT(ZoomIn()));
    connect(ui->pushButton_10, SIGNAL(clicked(bool)), this, SLOT(ZoomOut()));
    connect(ui->pushButton_11, SIGNAL(clicked(bool)), this, SLOT(PlusClassWidth()));
    connect(ui->pushButton_12, SIGNAL(clicked(bool)), this, SLOT(MinusClassWidth()));
    connect(ui->pushButton_13, SIGNAL(clicked(bool)), this, SLOT(PlusLineDistance()));
    connect(ui->pushButton_14, SIGNAL(clicked(bool)), this, SLOT(MinusLineDistance()));
    connect(ui->pushButton_15, SIGNAL(clicked(bool)), this, SLOT(DeleteNodeButton()));
    connect(ui->pushButton_16, SIGNAL(clicked(bool)), this, SLOT(OpenFileButton()));
    connect(ui->pushButton_17, SIGNAL(clicked(bool)), this, SLOT(SaveFileButton()));
    connect(ui->pushButton_18, SIGNAL(clicked(bool)), this, SLOT(UndoButton()));
    connect(ui->pushButton_19, SIGNAL(clicked(bool)), this, SLOT(CreateSequence()));

    mainModel = new Model;
    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    mainModel->SetScene(scene);
    mainModel->SetUndoStack(undoStack);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::UndoButton()
{
    /*
    model = new SequenceModel(mainModel);
    model->Test(scene, items);

    if(model->LoadFromFile("C:/Users/Radek/Desktop/skola/sracka.txt", mainModel, items, false) == 1)
    {
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Inconsistence detected", "Unknown methods and classes found. Do you want to add them to the class diagram?",
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes)
              model->LoadFromFile("C:/Users/Radek/Desktop/skola/sracka.txt", mainModel, items, true);
          else
          {
              delete model;
              return;
          }
    }


    model->SaveIntoFile("C:/Users/Radek/Desktop/skola/sracka2.txt");


    model->SaveIntoFile("C:/Users/Radek/Desktop/skola/sracka3.txt");
*/
    undoStack->undo();
    emit itemsChanged();
}

QList<ClassDiagramItem*> *MainWindow::GetItems()
{
    return &items;
}

void MainWindow::CreateSequence()
{
    SequenceModel *sequenceModel = new SequenceModel(mainModel);
    SequenceDiagramWindow *sequenceDiagram = new SequenceDiagramWindow(sequenceModel, this);
    sequenceDiagram->show();
    sequenceDiagrams.append(sequenceDiagram);
}

void MainWindow::SaveFileButton()
{
    QString file = QFileDialog::getSaveFileName();

    if(file.compare("") == 0)
        return;

    mainModel->SaveToFile(file.toStdString().c_str());
}

void MainWindow::OpenFileButton()
{
    QString file = QFileDialog::getOpenFileName();

    if(file.compare("") == 0)
        return;

    Model *tmp = mainModel;
    mainModel = new Model;
    delete tmp;

    mainModel->SetScene(scene);
    undoStack->clear();
    mainModel->SetUndoStack(undoStack);

    mainModel->LoadFromFile(file.toStdString().c_str());

    for(auto connection : connections)
        delete connection;

    items.clear();
    connections.clear();
    singletons.clear();


    undoStack->clear();

    for(auto entity : mainModel->GetEntities())
    {
        auto *item = new ClassDiagramItem(scene, entity);
        item->SetUndoStack(undoStack);
        items.append(item);
    }

    for(auto relation : mainModel->GetRelations())
    {
        if(relation->GetEntites().first == relation->GetEntites().second)
        {
            auto *item = new SingletonConnection(relation->GetEntites().first->GetView(),relation->GetEntites().first->GetView()->GetNode(relation->GetNode1()),
                                                 relation->GetEntites().first->GetView()->GetNode(relation->GetNode2()),relation);
            singletons.append(item);
        }
        else
        {
            auto *item = new Connection(scene, relation);
            connections.append(item);
        }
    }
    RefreshSequenceDiagrams();
}
/*
 *
    for(auto entity : mainModel->GetEntities())
    {
        auto command = new CreateClassCommand(mainModel, &items, scene, entity);
        undoStack->push(command);
        items.last()->SetUndoStack(undoStack);
    }

    for(auto relation : mainModel->GetRelations())
    {
        if(relation->GetEntites().first == relation->GetEntites().second)
        {
            auto *item = new SingletonConnection(relation->GetEntites().first->GetView(),relation->GetEntites().first->GetView()->GetNode(relation->GetNode1()),
                                                 relation->GetEntites().first->GetView()->GetNode(relation->GetNode2()),relation);
            singletons.append(item);
        }
        else
        {
            auto *item = new Connection(scene, relation);
            connections.append(item);
        }
    }*/

void MainWindow::RefreshSequenceDiagrams()
{
    for(auto diagram : sequenceDiagrams)
    {
        diagram->hide();
        delete diagram;
    }
    sequenceDiagrams.clear();
}

void MainWindow::AddClassButton()
{
    auto command = new CreateClassCommand(mainModel, &items, scene);
    undoStack->push(command);
    items.last()->SetUndoStack(undoStack);
    emit itemsChanged();
}

//removes rows from selected items
void MainWindow::RemoveRowButton()
{
    QList<QGraphicsItem*> selected = scene->selectedItems();

    //goes through all created items and selected item and compares
    for(auto rect : selected)
    {
        for(auto item : items)
        {
            if(rect == item->GetMainBody())
                item->RemoveRow();
        }
    }
}

void MainWindow::PlusLineDistance()
{
    //goes through all created items and selected item and compares
    for(auto selected : scene->selectedItems())
    {
        for(auto singleton : singletons)
        {
            if(singleton->GetMainLine() != selected)
                continue;
            singleton->SetDistance(singleton->GetDistance() + 20);
        }
    }
}

void MainWindow::MinusLineDistance()
{
    //goes through all created items and selected item and compares
    for(auto selected : scene->selectedItems())
    {
        for(auto singleton : singletons)
        {
            if(singleton->GetMainLine() != selected)
                continue;
            singleton->SetDistance(singleton->GetDistance() - 20);
        }
    }
}

//adds rows from selected items
void MainWindow::AddRowButton()
{
    QList<QGraphicsItem*> selected = scene->selectedItems();

    //goes through all created items and selected item and compares
    for(auto rect : selected)
    {
        for(auto item : items)
        {
            if(rect == item->GetMainBody())
                undoStack->push(new AddClassAttributeCommand(item));
        }
    }
}

void MainWindow::PlusClassWidth()
{
    for(auto rect : scene->selectedItems())
    {
        for(auto item : items)
        {
            if(rect == item->GetMainBody())
            {
                item->SetWidth(item->GetWidth() + 20);
            }
        }
    }
}

void MainWindow::MinusClassWidth()
{
    for(auto rect : scene->selectedItems())
    {
        for(auto item : items)
        {
            if(rect == item->GetMainBody())
                item->SetWidth(item->GetWidth() - 20);
        }
    }
}

//adds rows from selected items
void MainWindow::DeleteNodeButton()
{
    //goes through all created items and selected item and compares
    for(auto selected : scene->selectedItems())
    {
        int count {0};
        for(auto item : items)
        {
            if(selected != item->GetMainBody())
            {
                count++;
                continue;
            }

            std::vector<RelationEntity*> relations = item->GetModel()->GetRelations();
            for(auto relation : relations)
            {
                if(relation->GetEntites().first != relation->GetEntites().second)
                    delete relation->GetViewItem();
                mainModel->DeleteRelationById(relation->GetId());
            }

            mainModel->DeleteEntityById(item->GetModel()->GetId());
            items.removeAt(count);
            emit itemsChanged();
        }
        count = 0;
        for(auto connection : connections)
        {
            if(connection->GetMainLine() != selected)
            {
                count++;
                continue;
            }
            mainModel->DeleteRelationById(connection->GetModel()->GetId());
            delete connection;
            connections.removeAt(count);
        }
        count = 0;
        for(auto singleton : singletons)
        {
            if(singleton == nullptr)
                continue;
            if(singleton->GetMainLine() != selected)
            {
                count++;
                continue;
            }
            mainModel->DeleteRelationById(singleton->GetModel()->GetId());
            delete singleton;
            singletons.removeAt(count);
        }
    }
    undoStack->clear();
}

//adds rows from selected items
void MainWindow::RotateLineButton()
{
    QList<QGraphicsItem*> selected = scene->selectedItems();

    //goes through all created items and selected item and compares
    for(auto line : selected)
    {
        for(auto connection : connections)
        {
            if(line == connection->mainLine)
            {
                connection->Rotate();
            }
        }
    }
}

//adds rows from selected items
void MainWindow::ChangeLineButton()
{
    QList<QGraphicsItem*> selected = scene->selectedItems();

    //goes through all created items and selected item and compares
    for(auto line : selected)
    {
        for(auto connection : connections)
        {
            if(line == connection->mainLine)
            {
                connection->ChangeState();
            }
        }
    }

    //goes through all created items and selected item and compares
    for(auto selected : scene->selectedItems())
    {
        for(auto singleton : singletons)
        {
            if(singleton->GetMainLine() != selected)
                continue;
            singleton->ChangeState();
        }
    }
}

//adds rows from selected items
void MainWindow::MethodUpButton()
{
    QList<QGraphicsItem*> selected = scene->selectedItems();

    //goes through all created items and selected item and compares
    for(auto rect : selected)
    {
        for(auto item : items)
        {
            if(rect == item->GetMainBody())
                item->PushMethodUp();
        }
    }
}

//adds rows from selected items
void MainWindow::MethodDownButton()
{
    QList<QGraphicsItem*> selected = scene->selectedItems();

    //goes through all created items and selected item and compares
    for(auto rect : selected)
    {
        for(auto item : items)
        {
            if(rect == item->GetMainBody())
                item->PushMethodDown();
        }
    }
}

void MainWindow::AddSingletonLine()
{
}

//connects two selected item with line
void MainWindow::AddLine()
{
    QList<QGraphicsItem*> selected = scene->selectedItems();
    if(selected.count() == 1)
    {
        AddSingletonLine();
        return;
    }
    if(selected.count() != 2)
        return;
    ClassDiagramItem *item1 = nullptr;
    ClassDiagramItem *item2 = nullptr;
    QGraphicsEllipseItem *node1 = nullptr;
    QGraphicsEllipseItem *node2 = nullptr;

    //finds selected items
    for(auto item : items)
    {
        if(selected[0]->parentItem() == item->GetMainBody())
        {
            item1 = item;
            node1 = dynamic_cast<QGraphicsEllipseItem*>(selected[0]);
        }
        if(selected[1]->parentItem() == item->GetMainBody())
        {
            item2 = item;
            node2 = dynamic_cast<QGraphicsEllipseItem*>(selected[1]);
        }
    }

    if(item1 == nullptr || item2 == nullptr)
        return;

    if(item1 == item2)
        undoStack->push(new CreateSingletonCommand(mainModel, item1, node1, node2, &singletons));
    else
        undoStack->push(new CreateConnectionCommand(mainModel, item1, item2, node1, node2, &connections, scene));
}

void MainWindow::ZoomIn()
{
    ui->graphicsView->scale(1.25, 1.25);
}

void MainWindow::ZoomOut()
{
    ui->graphicsView->scale(0.8, 0.8);
}
