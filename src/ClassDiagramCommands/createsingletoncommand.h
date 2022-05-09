#ifndef CREATESINGLETONCOMMAND_H
#define CREATESINGLETONCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/DiagramEntity.h"
#include <QList>
#include "../ClsDiagItems/classdiagramitem.h"

class CreateSingletonCommand : public QUndoCommand
{
    public:
        CreateSingletonCommand(Model *model, ClassDiagramItem *item, QGraphicsEllipseItem *node1, QGraphicsEllipseItem *node2,
                               QList<SingletonConnection*> *singletons, QUndoCommand *parent = nullptr);
        void undo() override;
        void redo() override;

    private:
        ClassDiagramItem *item;
        SingletonConnection *singleton;
        Model *model;
        RelationEntity *relationEntity;
        QList<SingletonConnection*> *singletons;
        QGraphicsEllipseItem *node1;
        QGraphicsEllipseItem *node2;
};

#endif // CREATESINGLETONCOMMAND_H
