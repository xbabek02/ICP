/**
 * @file messageitem.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief QGraphicsItem message class
 * @version 0.1
 * @date 2022-05-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MESSAGEITEM_H
#define MESSAGEITEM_H

#include <QGraphicsLineItem>
#include <QString>
#include "rectangle.h"
#include "./Common/enums.h"
#include "./Entities/AttributeEntity.h"
#include "idcls.h"
#include "itemvisibility.h"

class Rectangle;

class MessageItem : public QGraphicsLineItem, public IDcls, public ItemVisibility
{
public:
    MessageItem(Enums::MessageTypes type, Rectangle* sender, int y, QGraphicsItem*parent = nullptr);
    Rectangle* sender = nullptr;
    Rectangle* owner = nullptr;

    bool solid = false;
    int startY;
    QRectF textRect;
    bool IsLeftToRight();
    QString method_str = "<No Method>";
    std::string *method_ptr;
    Enums::MessageTypes type;
    void SwitchSync();
    void UpdateDrawMessage(QPointF new_point);

private:

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;



};

#endif // MESSAGEITEM_H
