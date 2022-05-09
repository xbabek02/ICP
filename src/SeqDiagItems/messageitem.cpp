/**
 * @file messageitem.cpp
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief QGraphicsItem message class
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "messageitem.h"
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include "instanceitem.h"
#include "./Common/enums.h"
#include <QTextOption>

MessageItem::MessageItem(Enums::MessageTypes type, Rectangle *sender, int y, QGraphicsItem *parent)
    : QGraphicsLineItem(parent), IDcls(), ItemVisibility(), sender(sender), startY(y), type(type)
{
    if (type == Enums::MessageTypes::returnal)
    {
        setPen(QPen(Qt::black, 3, Qt::DashDotLine));
    }
    else
    {
        setPen(QPen(Qt::black, 3));
    }
    setLine(sender->instance->x() + InstanceItem::default_width / 2, startY, sender->instance->x() + InstanceItem::default_width / 2, startY);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}

bool MessageItem::IsLeftToRight()
{
    if (line().p1().x() < line().p2().x())
    {
        return true;
    }
    return false;
}

void MessageItem::SwitchSync()
{
    type = (type == Enums::MessageTypes::sync ? Enums::MessageTypes::async : Enums::MessageTypes::sync);
}

void MessageItem::UpdateDrawMessage(QPointF new_point)
{
    this->setLine(QLineF(line().p1(), new_point));
    update();
}

void MessageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 4));
    QTextOption option_txt;
    option_txt.setAlignment(Qt::AlignLeft);
    if (type == Enums::MessageTypes::async)
    {

        if (this->IsLeftToRight())
        {
            painter->drawLine(line().x2(), line().y2(), line().x2() - 10, line().y2() - 10);
            painter->drawLine(line().x2(), line().y2(), line().x2() - 10, line().y2() + 10);
            textRect.setRect(line().pointAt(0.23).x(), line().y1() - 30, 200, 25);
            painter->drawText(textRect, method_str, option_txt);
        }
        else
        {
            painter->drawLine(line().x2(), line().y2(), line().x2() + 10, line().y2() - 10);
            painter->drawLine(line().x2(), line().y2(), line().x2() + 10, line().y2() + 10);
            textRect.setRect(line().pointAt(0.77).x(), line().y1() - 30, 200, 25);
            painter->drawText(textRect, method_str, option_txt);
        }
    }
    else if (type == Enums::MessageTypes::sync)
    {
        int left = this->IsLeftToRight() ? 1 : -1;

        // Drawing Triangle
        // Start point of bottom line
        qreal startPointX1 = line().x2();
        qreal startPointY1 = line().y2();

        // End point of bottom line
        qreal endPointX1 = line().x2() - 10 * left;
        qreal endPointY1 = line().y2() - 10;

        // End point of top line
        qreal endPointX2 = line().x2() - 10 * left;
        qreal endPointY2 = line().y2() + 10;

        QPainterPath path;
        // Set pen to this point.
        path.moveTo(startPointX1, startPointY1);
        // Draw line from pen point to this point.
        path.lineTo(endPointX1, endPointY1);

        // path.moveTo (endPointX1, endPointY1); // <- no need to move
        path.lineTo(endPointX2, endPointY2);

        // path.moveTo (endPointX2,   endPointY2); // <- no need to move
        path.lineTo(startPointX1, startPointY1);
        painter->fillPath(path, QBrush(QColor("black")));

        // drawing text
        qreal point = this->IsLeftToRight() ? 0.23 : 0.77;
        textRect.setRect(line().pointAt(point).x(), line().y1() - 30, 200, 25);
        if (solid)
        {
            painter->drawText(textRect, method_str, option_txt);
        }
    }

    else if (type == Enums::returnal)
    {
        // setting the message name but warying possible rare exceptions
        if (sender)
        {
            if (sender->origin)
            {
                method_str = sender->origin->method_str;
            }
        }
        if (this->IsLeftToRight())
        {
            painter->drawLine(line().x2(), line().y2(), line().x2() - 10, line().y2() - 10);
            painter->drawLine(line().x2(), line().y2(), line().x2() - 10, line().y2() + 10);
            textRect.setRect(line().pointAt(0.23).x(), line().y1() - 30, 200, 25);
            painter->drawText(textRect, "return " + method_str, option_txt);
        }
        else
        {
            painter->drawLine(line().x2(), line().y2(), line().x2() + 10, line().y2() - 10);
            painter->drawLine(line().x2(), line().y2(), line().x2() + 10, line().y2() + 10);
            textRect.setRect(line().pointAt(0.77).x(), line().y1() - 30, 200, 25);
            painter->drawText(textRect, "return " + method_str, option_txt);
        }
        this->update();
    }
    QGraphicsLineItem::paint(painter, option, widget);
}

QRectF MessageItem::boundingRect() const
{
    QPainterPath pp;
    pp.addRect(QGraphicsLineItem::boundingRect());
    pp.addRect(line().x2() - 10, line().y2() - 10, 20, 20);
    pp.addRect(line().x1() - 10, line().y2() - 10, 20, 20);
    if (!textRect.isNull())
        pp.addRect(textRect);

    return pp.boundingRect();
}
