#include "rectangle.h"
#include "instanceitem.h"
#include "messageitem.h"
#include <QBrush>
#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>

int Rectangle::width = 25;
int Rectangle::min_length = 50;
Rectangle*Rectangle::initial_block = nullptr;
int Rectangle::colision_offset = 5;

int Rectangle::GetLength()
{
    return length + addedLength;
}

void Rectangle::UpdateRectangle()
{
    update();
    UpdateReturnal();

}

void Rectangle::SetBaseLength(int length)
{
    this->length = length;
}

void Rectangle::AddRemoveLength(int added)
{
    addedLength += added;
    if (addedLength < 0) {
        addedLength = 0;
    }
}


Rectangle::Rectangle(QGraphicsItem *parent, MessageItem*origin, int offset) :
    QGraphicsRectItem(parent), length(min_length), origin(origin),
    addedLength(0), vertical_offset(offset), IDcls()
{
    if (!(instance = dynamic_cast<InstanceItem*>(parent))){
        qDebug("Bad Dynamic cast in Rectangle constructor");
        return;
    }
    instance->rectangles.append(this);

    setBrush(QBrush(Qt::white));
    setPen(QPen(Qt::black, 4));

    setRect(instance->width/2 - width/2, offset, width, length);
    update();
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void Rectangle::AddMessage(MessageItem *m)
{
    sent.append(m);
    UpdateLengths();
}

void Rectangle::UpdateLengths()
{
   if (initial_block != nullptr){
       initial_block->UpdateLengthsRec();
       initial_block->update();
   }
}

void Rectangle::UpdateReturnal()
{
    if (!this->return_message){
        return;
    }

    int y_cord = GetEndOfBlock();
    if (return_message->line().isNull()){
        return;
    }
    if (y_cord != return_message->line().y1()){
        return_message->setLine(return_message->line().x1(), y_cord, return_message->line().x2(), y_cord);
        return_message->update();
    }
}

int Rectangle::GetEndOfBlock()
{
    return scenePos().y() + vertical_offset + GetLength();
}

int Rectangle::GetStartOfBlock()
{
    return scenePos().y() + vertical_offset;
}

int Rectangle::UpdateLengthsRec()
{
    int length_total = min_length;

    for (auto message : sent) {
        message->owner->UpdateLengthsRec();
        length_total += message->owner->GetLength();
    }

    SetBaseLength(length_total);
    UpdateRectangle();
    return length_total;
}

void Rectangle::update(const QRectF &rect)
{
    Rectangle*rectangle;
    bool found_some = false;
    bool found_already_nested = false;
    for (auto colider : collidingItems()){
        rectangle = dynamic_cast<Rectangle*>(colider);
        if (rectangle){
           found_some = true;
           if (rectangle->nested){
               found_already_nested = true;
           }
        }
    }

    if (!found_already_nested && found_some){
        setRect(instance->width/2 + colision_offset - width/2, vertical_offset, width, GetLength());
        nested = true;
    }
    else {
        setRect(instance->width/2 - width/2, vertical_offset, width, GetLength());
    }


    QGraphicsRectItem::update(rect);
}
