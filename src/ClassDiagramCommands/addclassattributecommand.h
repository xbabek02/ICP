#ifndef ADDCLASSATTRIBUTECOMMAND_H
#define ADDCLASSATTRIBUTECOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/DiagramEntity.h"
#include <QList>
#include "../ClsDiagItems/classdiagramitem.h"
#include <QUndoStack>
#include <QGraphicsObject>
#include <QObject>

class AddClassAttributeCommand : public QUndoCommand
{
public:
    explicit AddClassAttributeCommand(ClassDiagramItem *item, QUndoCommand *parent = nullptr);
    ~AddClassAttributeCommand(){}
    void undo() override;
    void redo() override;

private:
    ClassDiagramItem *item;
};

#endif // ADDCLASSATTRIBUTECOMMAND_H
