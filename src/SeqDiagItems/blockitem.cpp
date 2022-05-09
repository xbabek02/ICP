#include "blockitem.h"
#include "instanceitem.h"

#include <QPainter>
#include <QPen>
#include <QDebug>

int BlockItem::width = 20;
int BlockItem::min_length = 50;


BlockItem::BlockItem(QGraphicsItem *parent, MessageItem*origin, int offsetY)
    : QGraphicsRectItem(parent), origin(origin), length(min_length), offsetY(offsetY)
{
    ii = dynamic_cast<InstanceItem*>(parent);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void BlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->setBrush(Qt::white);
    painter->setPen(QPen(Qt::black, 2));

    painter->drawRect(ii->x - width/2, ii->startY + offsetY, width, length);


    painter->setPen(QPen(Qt::red, 3));
    painter->drawRect(boundingRect());
}

QRectF BlockItem::boundingRect() const {
    return QRectF(ii->x - width/2, ii->startY + offsetY, width, length);
}

void BlockItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}







