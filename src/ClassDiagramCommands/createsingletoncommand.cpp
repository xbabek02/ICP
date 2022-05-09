#include "createsingletoncommand.h"

CreateSingletonCommand::CreateSingletonCommand(Model *model, ClassDiagramItem *item, QGraphicsEllipseItem *node1,
                                               QGraphicsEllipseItem *node2, QList<SingletonConnection*> *singletons, QUndoCommand *parent) : QUndoCommand(parent)
{
    this->item = item;
    this->model = model;
    this->singletons = singletons;
    this->node1 = node1;
    this->node2 = node2;
}

void CreateSingletonCommand::undo()
{
    delete singleton->GetModel();
    delete singleton;
    singletons->removeLast();
}

void CreateSingletonCommand::redo()
{
    DiagramEntity &ref1 = *item->GetModel();
    RelationEntity *relationModel = model->CreateRelation(ref1, ref1);
    relationModel->ChangeNode1(item->GetNodeID(node1));
    relationModel->ChangeNode2(item->GetNodeID(node2));
    singleton = new SingletonConnection(item, node1, node2, relationModel);
    singletons->append(singleton);
}
