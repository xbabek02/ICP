#include "textitem_instance.h"
#include "instanceitem.h"
#include <QFont>

TextItemInstance::TextItemInstance(QGraphicsItem  *parent)
    : QGraphicsTextItem(parent), IDcls()
{
    id = 0;
    setTextInteractionFlags(Qt::TextEditable);
    QFont font;
    font.setPointSize(font.pointSize() * 1.2);
    setFont(font);
}

void TextItemInstance::keyReleaseEvent(QKeyEvent * event)
{
    //emit valueChanged(toPlainText());
    auto inst = dynamic_cast<InstanceItem*>(parentItem());
    if (inst){
        inst->text_name = toPlainText();
    }

    QGraphicsTextItem::keyReleaseEvent(event);
}

void TextItemInstance::SetId(int id)
{
    this->id = id;
}

int TextItemInstance::GetId()
{
    return id;
}

void TextItemInstance::setText(QString value)
{
    setPlainText(value);
}

void TextItemInstance::SetLock(bool lock)
{
    if(lock)
        setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    else
        setTextInteractionFlags(Qt::TextEditorInteraction);
}
