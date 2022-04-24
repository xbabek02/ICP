#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QGraphicsTextItem>
#include <QGraphicsItemGroup>
#include "classdiagramitem.h"
#include <typeinfo>
#include "connectline.h"

QGraphicsScene *scene;
QList<ClassDiagramItem*> items;
ClassDiagramItem *item;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //connects button functions to buttons
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(AddRowButton()));
    connect(ui->pushButton_2, SIGNAL(clicked(bool)), this, SLOT(RemoveRowButton()));
    connect(ui->pushButton_3, SIGNAL(clicked(bool)), this, SLOT(AddClassButton()));
    connect(ui->pushButton_4, SIGNAL(clicked(bool)), this, SLOT(AddLine()));

    scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddClassButton()
{
    auto *item = new ClassDiagramItem(scene);
    items.append(item);
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
            if(rect == item->mainBody)
                item->RemoveRow();
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
            if(rect == item->mainBody)
                item->AddRow();
        }
    }
}

//connects two selected item with line
void MainWindow::AddLine()
{
    QList<QGraphicsItem*> selected = scene->selectedItems();
    if(selected.count() != 2)
        return;
    ClassDiagramItem *item1;
    ClassDiagramItem *item2;

    //finds selected items
    for(auto item : items)
    {
        if(selected[0] == item->mainBody)
            item1 = item;
        if(selected[1] == item->mainBody)
            item2 = item;
    }

    //creates new line
    ConnectLine *line = new ConnectLine(item1, item2);
    scene->addItem(line);
}
