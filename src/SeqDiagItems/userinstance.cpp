#include "userinstance.h"
#include <QPainter>
#include <QImage>

UserInstance::UserInstance(QGraphicsItem *parent)
    : InstanceItem(parent)
{
    ti->setVisible(false);
    text_name = "User";
}

void UserInstance::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    //;painter->setBrush(Qt::black);
    painter->setPen(QPen(Qt::black, 3));
    QFont font = painter->font();

    font.setPointSize(font.pointSize() * 1.3);

    /* set the modified font to the painter */
    painter->setFont(font);

    painter->drawLine(default_x, default_y+70, default_x + width, default_y+70);


    painter->drawText(QRectF(default_x, default_y, width, 50),Qt::AlignCenter, text_class);
    painter->drawLine(default_x+ width /2, default_y + 70, default_x + width / 2, default_y + length);

    painter->drawImage(QRect(default_x+10, default_y, 60, 60), QImage("../user.png"));

    //QGraphicsItem::paint(painter, option, widget);
}

QRectF UserInstance::boundingRect() const {
     return QRectF(default_x, default_y, width, length + 55);
}
