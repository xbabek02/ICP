#include "messageline.h"

MessageLine::MessageLine(QGraphicsItem*parent)
    :QGraphicsLineItem(parent)
{
    setLine(this->parent->x, this->parent->startY+2, this->parent->x, this->parent->startY + length);
}

void MessageLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->setPen(QPen(Qt::darkGray, 2));

    painter->drawLine(line());

}
