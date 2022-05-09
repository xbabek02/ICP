/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "classitemhead.h"
#include <QPen>
#include <QBrush>
#include <QDebug>

//class diagram class head -> movable rectangle
ClassItemHead::ClassItemHead(int width, int height, QGraphicsRectItem *parent1, QObject *parent2)
    : QObject(parent2), QGraphicsRectItem(parent1)
{
    this->width = width;
    this->height = height;

    //creates rectangle
    setRect(0,0,width,30);
    setPen(QPen{Qt::darkGray, 2});
    setBrush(QBrush{Qt::darkGray});

    //sets to movable and selectable
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void ClassItemHead::SetWidth(int value)
{
    prepareGeometryChange();
    width = value;
    setRect(0,0,width,30);
}

void ClassItemHead::SetHeight(int value)
{
    prepareGeometryChange();
    height = value;
}

void ClassItemHead::EmitPositionSignal()
{
    emit positionChange(this->pos());
}

void ClassItemHead::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    emit mouseReleaseSignal(scenePos());
    return QGraphicsItem::mouseReleaseEvent(event);
}

void ClassItemHead::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //creates signal when mouse moves this object
    QGraphicsRectItem::mouseMoveEvent(event);
    emit positionChange(this->pos());
}

QVariant ClassItemHead::itemChange(GraphicsItemChange change, const QVariant &value)
{
    emit positionChange(this->pos());
    return QGraphicsItem::itemChange(change, value);
}

QRectF ClassItemHead::boundingRect() const
{
    return QRectF(-150, -150, width + 150 * 2, height + 150 * 2);
}
