/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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
