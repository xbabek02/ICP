#ifndef INSTANCELINE_H
#define INSTANCELINE_H

#include <QGraphicsLineItem>
#include <QObject>
#include "instanceitem.h"
#include "blockitem.h"
#include <vector>


class InstanceLine : public QGraphicsLineItem
{
public:
    InstanceLine(QGraphicsItem *parent);
    std::vector<BlockItem*> blockItems;

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override ;
    //QRectF boundingRect() const;

private:
    int length;
    InstanceItem*parent;

};

#endif // INSTANCELINE_H

