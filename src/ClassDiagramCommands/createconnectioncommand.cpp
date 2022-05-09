#include "createconnectioncommand.h"

CreateConnectionCommand::CreateConnectionCommand(Model *model, ClassDiagramItem *item1, ClassDiagramItem *item2, QGraphicsEllipseItem *node1,
                                                 QGraphicsEllipseItem *node2, QList<Connection*> *connections,QGraphicsScene *scene, QUndoCommand *parent)
                                                 : QUndoCommand(parent)
{
    this->scene = scene;
    this->item1 = item1;
    this->item2 = item2;
    this->model = model;
    this->connections = connections;
    this->node1 = node1;
    this->node2 = node2;
}

void CreateConnectionCommand::undo()
{
    delete connection->GetModel();
    delete connection;
    connections->removeLast();
}

void CreateConnectionCommand::redo()
{
    DiagramEntity &ref1 = *item1->GetModel();
    DiagramEntity &ref2 = *item2->GetModel();
    relationModel = model->CreateRelation(ref1, ref2);
    relationModel->ChangeNode1(item1->GetNodeID(node1));
    relationModel->ChangeNode2(item2->GetNodeID(node2));

    connection = new Connection(scene, relationModel, node1, node2);
    connections->append(connection);
}
