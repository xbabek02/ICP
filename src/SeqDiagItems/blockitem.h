#ifndef BLOCKITEM_H
#define BLOCKITEM_H

#include <QGraphicsRectItem>
#include "instanceitem.h"
#include "messageitem.h"
#include <QList>
#include <QObject>

class InstanceItem;
class MessageItem;

class BlockItem : public QGraphicsRectItem
{
public:
    static int min_length;
    static int width;
    BlockItem(QGraphicsItem *parent = nullptr, int offsetY = 40);
    InstanceItem*ii;
    QList<MessageItem*> messages;
    QRectF boundingRect() const;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

protected:

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override ;
    int length;
    int offsetY;

signals:
    void ClickSignal();


};

#endif // BLOCKITEM_H
