#include "classmovecommand.h"

ClassMoveCommand::ClassMoveCommand(ClassDiagramItem *item, QUndoStack *undoStack, QUndoCommand *parent)
    : QUndoCommand(parent)
{
    this->item = item;
    this->undoStack = undoStack;
}

void ClassMoveCommand::undo()
{
    item->LastPosition();
}

void ClassMoveCommand::redo()
{
}

ClassMoveCommand::~ClassMoveCommand(){}
