#ifndef CREATECLASSCOMMAND_H
#define CREATECLASSCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/DiagramEntity.h"
#include <QList>
#include "../ClsDiagItems/classdiagramitem.h"

class CreateClassCommand : public QUndoCommand
{
public:
    CreateClassCommand(Model *mainModel, QList<ClassDiagramItem*> *items, QGraphicsScene *scene, DiagramEntity *entity = nullptr, QUndoCommand *parent = nullptr);
    void undo() override;
    void redo() override;

private:
    DiagramEntity *createdItem = nullptr;
    QGraphicsScene *scene;
    Model *mainModel;
    QList<ClassDiagramItem*> *items;
    QPointF lastPosition;
};

#endif // CREATECLASSCOMMAND_H
