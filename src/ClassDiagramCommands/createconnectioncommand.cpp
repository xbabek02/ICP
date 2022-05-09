/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "createconnectioncommand.h"

CreateConnectionCommand::CreateConnectionCommand(Model *model, ClassDiagramItem *item1, ClassDiagramItem *item2, QGraphicsEllipseItem *node1,
                                                 QGraphicsEllipseItem *node2, QList<Connection*> *connections,QGraphicsScene *scene,
                                                 RelationEntity *entity, QUndoCommand *parent) : QUndoCommand(parent)
{
    this->scene = scene;
    this->item1 = item1;
    this->item2 = item2;
    this->model = model;
    this->connections = connections;
    this->node1 = node1;
    this->node2 = node2;
    this->relationModel = entity;
}

CreateConnectionCommand::CreateConnectionCommand(QGraphicsScene *scene, RelationEntity *relation)
{
    this->scene = scene;
    relationModel = relation;
}

void CreateConnectionCommand::undo()
{
    delete connection->GetModel();
    delete connection;
    connections->removeLast();
}

void CreateConnectionCommand::redo()
{
    if(item1 != nullptr)
    {
        DiagramEntity &ref1 = *item1->GetModel();
        DiagramEntity &ref2 = *item2->GetModel();
        if(relationModel == nullptr)
            relationModel = model->CreateRelation(ref1, ref2);
        relationModel->ChangeNode1(item1->GetNodeID(node1));
        relationModel->ChangeNode2(item2->GetNodeID(node2));
        connection = new Connection(scene, relationModel, node1, node2);
    }
    else
    {
        connection = new Connection(scene, relationModel);
    }

    connections->append(connection);
}
