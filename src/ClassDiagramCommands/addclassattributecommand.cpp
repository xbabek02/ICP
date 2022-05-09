/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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
