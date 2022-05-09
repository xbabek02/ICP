#include "deleteclasscommand.h"

DeleteClassCommand::DeleteClassCommand(ClassDiagramItem *item, QUndoCommand *parent) : QUndoCommand(parent)
{
    this->item = item;
}

void DeleteClassCommand::undo()
{
    item->GetMainBody()->setVisible(true);
}

void DeleteClassCommand::redo()
{
    item->GetMainBody()->setVisible(false);
}
