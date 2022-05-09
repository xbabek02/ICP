#include "addclassattributecommand.h"

AddClassAttributeCommand::AddClassAttributeCommand(ClassDiagramItem *item, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    this->item = item;
}

void AddClassAttributeCommand::undo()
{
    item->RemoveRow();
}

void AddClassAttributeCommand::redo()
{
    item->NewRow(Qt::gray);
}
