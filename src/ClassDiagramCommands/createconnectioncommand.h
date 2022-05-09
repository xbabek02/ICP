#ifndef CREATECONNECTIONCOMMAND_H
#define CREATECONNECTIONCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/RelationEntity.h"
#include <QList>
#include "../ClsDiagItems/connection.h"

class CreateConnectionCommand : public QUndoCommand
{
    public:
        CreateConnectionCommand(Model *model, ClassDiagramItem *item1, ClassDiagramItem *item2, QGraphicsEllipseItem *node1, QGraphicsEllipseItem *node2,
                                QList<Connection*> *connections, QGraphicsScene *scene, QUndoCommand *parent = nullptr);
        void undo() override;
        void redo() override;

    private:
        Connection *connection;
        QGraphicsScene *scene;
        Model *model;
        QList<Connection*> *connections;
        RelationEntity *relationModel;
        ClassDiagramItem *item1;
        ClassDiagramItem *item2;
        QGraphicsEllipseItem *node1;
        QGraphicsEllipseItem *node2;
};

#endif // CREATECONNECTIONCOMMAND_H
