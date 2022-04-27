#include "classitemhead.h"
#include <QPen>
#include <QBrush>
#include <QDebug>

//class diagram class head -> movable rectangle
ClassItemHead::ClassItemHead(QGraphicsRectItem *parent1, QObject *parent2)
    : QObject(parent2), QGraphicsRectItem(parent1)
{
    //creates rectangle
    setRect(0,0,100,30);
    setPen(QPen{Qt::black, 2});
    setBrush(QBrush{Qt::gray});

    //sets to movable and selectable
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void ClassItemHead::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //creates signal when mouse moves this object
    QGraphicsRectItem::mouseMoveEvent(event);
    emit positionChange(this->pos());
}

