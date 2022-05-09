/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "textitem.h"

TextItem::TextItem(QGraphicsItem  *parent)
    : QGraphicsTextItem(parent)
{
    id = 0;
    setTextInteractionFlags(Qt::TextEditorInteraction);
}

void TextItem::keyReleaseEvent(QKeyEvent * event)
{
    emit valueChanged(toPlainText(), id);
    QGraphicsTextItem::keyReleaseEvent(event);
}

void TextItem::SetId(int id)
{
    this->id = id;
}

int TextItem::GetId()
{
    return id;
}

void TextItem::setText(QString value)
{
    setPlainText(value);
}

void TextItem::SetLock(bool lock)
{
    if(lock)
        setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    else
        setTextInteractionFlags(Qt::TextEditorInteraction);
}
