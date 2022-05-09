#ifndef USERINSTANCE_H
#define USERINSTANCE_H

#include "instanceitem.h"

class UserInstance : public InstanceItem
{
public:
    UserInstance(QGraphicsItem *parent = nullptr);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override ;
    QRectF boundingRect() const;
};

#endif // USERINSTANCE_H
