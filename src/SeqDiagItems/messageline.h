#ifndef MESSAGELINE_H
#define MESSAGELINE_H

#include <QGraphicsLineItem>
#include <./Common/enums.h>

class MessageLine : public QGraphicsLineItem
{
public:
    MessageLine(QGraphicsItem *parent);
    Enums::MessageTypes type;

protected:
     QRectF boundingRect() const;

     virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override ;


};

#endif // MESSAGELINE_H
