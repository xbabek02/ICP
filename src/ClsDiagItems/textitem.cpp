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
