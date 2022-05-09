#include "createclasscommand.h"

CreateClassCommand::CreateClassCommand(Model *mainModel, QList<ClassDiagramItem*> *items, QGraphicsScene *scene, QUndoCommand *parent) : QUndoCommand(parent)
{
    this->scene = scene;
    this->mainModel = mainModel;
    this->items = items;
}

void CreateClassCommand::undo()
{
    mainModel->DeleteEntity(mainModel->GetEntities()[mainModel->GetEntities().size() - 1]);
}

void CreateClassCommand::redo()
{
    createdItem = mainModel->CreateEntity("class_name");
    auto *item = new ClassDiagramItem(scene, createdItem);
    items->append(item);
    createdItem->GetView()->GetMainBody()->setPos(lastPosition);
}
