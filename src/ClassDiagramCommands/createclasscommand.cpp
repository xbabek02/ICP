/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "createclasscommand.h"

CreateClassCommand::CreateClassCommand(Model *mainModel, QList<ClassDiagramItem*> *items, QGraphicsScene *scene,
                                       DiagramEntity *entity, QUndoCommand *parent) : QUndoCommand(parent)
{
    this->scene = scene;
    this->mainModel = mainModel;
    this->items = items;
    createdItem = entity;
}

void CreateClassCommand::undo()
{
    mainModel->DeleteEntity(mainModel->GetEntities()[mainModel->GetEntities().size() - 1]);
}

void CreateClassCommand::redo()
{
    if(createdItem == nullptr)
        createdItem = mainModel->CreateEntity("class_name");
    auto *item = new ClassDiagramItem(scene, createdItem);
    items->append(item);
    createdItem->GetView()->GetMainBody()->setPos(lastPosition);
}
