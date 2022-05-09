#include "sequencediagramwindow.h"
#include "ui_sequencediagramwindow.h"
#include "./Models/classesmodel.h"
#include "./Models/methodmodel.h"
#include "./Models/instancesmodel.h"
#include "./Models/seqdscene.h"
#include "./SeqDiagItems/instanceitem.h"
#include "./Entities/DiagramEntity.h"
#include "./SeqDiagItems/rectangle.h"
#include "./Common/enums.h"
#include "mainwindow.h"

#include <QString>
#include <QDebug>

SequenceDiagramWindow::SequenceDiagramWindow(SequenceModel *sequenceModel, MainWindow *mainWindow, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SequenceDiagramWindow)
{
    ui->setupUi(this);

    this->mainWindow = mainWindow;
    this->sequenceModel = sequenceModel;

    mm = new MethodModel(ui->methodView);
    ui->methodView->setModel(mm);

    InitScene(mm);

    ui->classesView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->methodView->setSelectionMode(QAbstractItemView::ExtendedSelection);

    //connects button functions to buttons
    connect(ui->createInstanceButton, SIGNAL(clicked(bool)), this, SLOT(CreateInstance()));
    connect(ui->deleteInstanceButton, SIGNAL(clicked(bool)), this, SLOT(DeleteInstance()));
    connect(ui->prolongueButton, SIGNAL(clicked(bool)), this, SLOT(ProlongueLine()));
    connect(ui->shortenButton, SIGNAL(clicked(bool)), this, SLOT(ShortenLine()));
    connect(ui->visibilityButton, SIGNAL(clicked(bool)), this, SLOT(ChangeVisibility()));
    connect(ui->addInitBlockButton, SIGNAL(clicked(bool)), this, SLOT(AddInitialBlock()));
    connect(ui->prolongueBlockButton, SIGNAL(clicked(bool)), this, SLOT(ProlongueBlock()));
    connect(ui->shortenBlockButton, SIGNAL(clicked(bool)), this, SLOT(ShortenBlock()));
    connect(ui->syncAsyncButton, SIGNAL(clicked(bool)), this, SLOT(SwitchSyncAsync()));
    connect(ui->returnMessageButton, SIGNAL(clicked(bool)), this, SLOT(ReturnMessage()));
    connect(ui->setMethodButton, SIGNAL(clicked(bool)), this, SLOT(SetMethod()));
    connect(ui->saveFileButton, SIGNAL(clicked(bool)), this, SLOT(SaveFile()));
    connect(ui->openFileButton, SIGNAL(clicked(bool)), this, SLOT(OpenFile()));

    //setting up models
    cm = new ClassesModel(sequenceModel->GetMainModel(), ui->classesView);
    ui->classesView->setModel(cm);

    im = new InstancesModel(ui->instancesView, user);
    ui->instancesView->setModel(im);
    this->sequenceModel->SetInstancesModel(im);

    connect(mainWindow, SIGNAL(itemsChanged()), cm, SLOT(loadData()));
}

SequenceDiagramWindow::~SequenceDiagramWindow()
{
    for (auto ii : instanceItems){
        delete ii;
    }
    delete user;

    delete cm;
    delete scene;
    delete ui;
}

void SequenceDiagramWindow::InitScene(MethodModel*mm){
    scene = new SeqDScene(mm, ui->graphicsView);

    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);


    user = new UserInstance();
    user->text_class = "User";
    scene->addItem(user);
}


/* BUTTON FUNCTIONS */
void SequenceDiagramWindow::CreateInstance(){
    QModelIndex index = ui->classesView->currentIndex();
    auto de = index.data(Qt::UserRole).value<DiagramEntity*>();
    if (index.isValid()){
        //create instance in model
        InstanceItem* ii = new InstanceItem(nullptr, de, QString::fromStdString(de->GetName()));

        this->instanceItems.append(ii);
        this->im->addRow(ii);


        scene->addItem(ii);
        scene->setFocusItem(ii);

        ii->MoveIfObstructed(1);
    }
}

void SequenceDiagramWindow::DeleteInstance(){
    QModelIndex index = ui->instancesView->currentIndex();
    auto ii = index.data(Qt::UserRole).value<InstanceItem*>();

    if (index.isValid()){
       if (dynamic_cast<UserInstance*>(ii)){
            im->SwitchVisible(ii->GetID());
            return;
       }

       for (auto rectangle : ii->rectangles){
           scene->DeleteRectangle(rectangle);
       }

        this->im->removeRow(index);
        scene->removeItem(ii);

        delete ii;
    }
}

void SequenceDiagramWindow::SaveFile()
{
    sequenceModel->LoadFromAppState();
    QString file = QFileDialog::getSaveFileName();
    sequenceModel->SaveIntoFile(file.toStdString().c_str());
}

void SequenceDiagramWindow::OpenFile()
{
    QString file = QFileDialog::getOpenFileName();

    if(file.compare("") == 0)
        return;
    sequenceModel->Clear();

    if(sequenceModel->LoadFromFile(file.toStdString().c_str(), sequenceModel->GetMainModel(), mainWindow->GetItems(), false) == 1)
    {
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Inconsistence detected", "Unknown methods and classes found. Do you want to add them to the class diagram?",
                                        QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes)
              sequenceModel->LoadFromFile(file.toStdString().c_str(), sequenceModel->GetMainModel(), mainWindow->GetItems(), true);
          else
              return;
    }
    SeqDScene *newscene = new SeqDScene(mm, ui->graphicsView);
    sequenceModel->LoadToAppState(newscene);
    auto aux = scene;
    ui->graphicsView->setScene(newscene);
    delete aux;
}

void SequenceDiagramWindow::ProlongueLine(){
    QModelIndex index = ui->instancesView->currentIndex();
    auto ii = index.data(Qt::UserRole).value<InstanceItem*>();

    if (index.isValid()){
        ii->length += 50;
        ii->update();
        scene->update();
    }
}
void SequenceDiagramWindow::ShortenLine(){
    QModelIndex index = ui->instancesView->currentIndex();
    auto ii = index.data(Qt::UserRole).value<InstanceItem*>();

    if (index.isValid()){
       if (ii->length-50 >= ii->default_length-100){
           ii->length -= 50;
           ii->update();
           scene->update();
       }
    }
}
void SequenceDiagramWindow::ChangeVisibility(){
    //get selected item from instancesView
    QModelIndex index = ui->instancesView->currentIndex();
    auto ii = index.data(Qt::UserRole).value<InstanceItem*>();
    if (!index.isValid()){
        return;
    }
    im->SwitchVisible(ii->GetID());
    QList<QGraphicsItem *> *list = scene->GetAllDependentOwnRectFree(ii);
    for (QGraphicsItem *item : *list){
        auto visibility = dynamic_cast<ItemVisibility*>(item);
        visibility->SetDependency(ii->GetID(), ii->isVisible());
        item->setVisible(visibility->Visible());
    }
    ii->setVisible(!ii->isVisible());
    delete list;
}

void SequenceDiagramWindow::AddInitialBlock() {
    //only one initial block allowed
    if (Rectangle::initial_block){
        return;
    }

    //get selected item from instancesView
    QModelIndex index = ui->instancesView->currentIndex();
    auto ii = index.data(Qt::UserRole).value<InstanceItem*>();
    if (!index.isValid()){
        return;
    }

    Rectangle *item = new Rectangle(ii, nullptr, 70 + 20);
    ii->update();
    Rectangle::initial_block = item;
}

void SequenceDiagramWindow::ProlongueBlock()
{
    Rectangle*selected;
    for (auto item : scene->selectedItems()){
        selected = dynamic_cast<Rectangle*>(item);
        if (selected) {
            selected->AddRemoveLength(Rectangle::min_length);
        }
    }
    Rectangle::UpdateLengths();
}

void SequenceDiagramWindow::ShortenBlock()
{
    Rectangle*selected;
    for (auto item : scene->selectedItems()){
        selected = dynamic_cast<Rectangle*>(item);
        if (selected) {
            selected->AddRemoveLength(-Rectangle::min_length);
        }
    }
    Rectangle::UpdateLengths();
}

void SequenceDiagramWindow::SwitchSyncAsync()
{
    MessageItem*selected;
    for (auto item : scene->selectedItems()){
        selected = dynamic_cast<MessageItem*>(item);
        if (selected) {
            if (selected->type == Enums::MessageTypes::returnal){
                return;
            }
            selected->SwitchSync();
            selected->update();
        }
    }
}

void SequenceDiagramWindow::ReturnMessage()
{
    Rectangle*selected;
    for (auto item : scene->selectedItems()){
        selected = dynamic_cast<Rectangle*>(item);
        if (selected) {
            if (!selected->return_message){ // no return message, then create one
                if (!selected->origin) { //if is initial block
                    continue;
                }
                int x1 = selected->scenePos().x() + InstanceItem::default_width/2 ;
                int y = selected->GetEndOfBlock();
                selected->origin->update();
                int x2 = selected->origin->sender->scenePos().x() + InstanceItem::default_width/2 + selected->width/2;
                selected->return_message = new MessageItem(Enums::MessageTypes::returnal, selected, y);

                if (x1 < x2){ //left to right returnal
                    selected->return_message->setLine(x1 + selected->width/2,y,x2-Rectangle::width, y);
                }
                else{ //rigth to left returnal
                    selected->return_message->setLine(x1 - selected->width/2, y, x2, y);
                }
                scene->addItem(selected->return_message);
                selected->return_message->owner = selected->origin->sender;
                selected->origin->sender->returning_messages.append(selected->return_message);

                selected->return_message->update();
            }
            else{ // delete return message,
                scene->DeleteMessage(selected->return_message);
            }
        }
    }
    Rectangle::UpdateLengths();
}

void SequenceDiagramWindow::SetMethod()
{
    QModelIndex index = ui->methodView->currentIndex();
    auto value = index.data(Qt::DisplayRole);
    if (index.isValid()){
        //create instance in model
    }
    mm->currently_displayed->method_str = value.toString();
    mm->currently_displayed->update();
    if (mm->currently_displayed->owner->return_message){
        mm->currently_displayed->owner->return_message->update();
    }
}
