#ifndef DELETECLASSCOMMAND_H
#define DELETECLASSCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/DiagramEntity.h"
#include <QList>
#include "../ClsDiagItems/classdiagramitem.h"

class DeleteClassCommand : public QUndoCommand
{
public:
    DeleteClassCommand(ClassDiagramItem *item, QUndoCommand *parent = nullptr);
    void undo() override;
    void redo() override;

private:
    ClassDiagramItem *item;
};

#endif // DELETECLASSCOMMAND_H
