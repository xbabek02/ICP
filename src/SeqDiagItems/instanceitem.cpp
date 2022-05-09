#include "instanceitem.h"

#include <QPen>
#include <QDebug>
#include <QtGui>
#include <QRectF>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include "userinstance.h"

int InstanceItem::default_y = 0;
int InstanceItem::default_x = 0;
int InstanceItem::default_length = 500;
int InstanceItem::default_width = 80;
int InstanceItem::distance = 100;


int InstanceItem::MoveIfObstructed(int direction){
    bool moved = true;
    int total_distance_moved = 0;
    while (moved) {
        moved = false;
        //moving objects

        auto coliders = collidingItems();
        for (auto colider : coliders){
            if (dynamic_cast<InstanceItem*>(colider)){
                setPos(pos() + QPointF(direction*distance,0));
                moved = true;
                total_distance_moved += distance;
                break;
            }
        }
    }
    return total_distance_moved;
}

InstanceItem::InstanceItem(QGraphicsItem *parent, DiagramEntity*classEntity, QString text) :
    QGraphicsItem(parent), IDcls(), classEntity(classEntity), text_class(text),
    length(default_length), width(default_width)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsFocusable);
    ti = new TextItemInstance(this);
    ti->setPlainText(text_name);
    ti->moveBy(0, 20);

    //setHandlesChildEvents(false);
}

void InstanceItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    //;painter->setBrush(Qt::black);
    painter->setPen(QPen(Qt::black, 3));
    painter->drawLine(default_x, default_y+70, default_x + width, default_y+70);

    painter->drawLine(default_x+ width /2, default_y + 70, default_x + width / 2, default_y + length);

    painter->drawText(QRectF(default_x, default_y, width, 20),Qt::AlignCenter, "<" + text_class + ">");
}

QRectF InstanceItem::boundingRect() const {
     return QRectF(default_x, default_y, width, length+55);
}

void InstanceItem::keyPressEvent(QKeyEvent *event){
    int total_distance_moved = 0;
    switch (event->key()){
    case Qt::Key_Right:
        setPos(pos() + QPointF(distance,0));
        total_distance_moved += distance;

        total_distance_moved += MoveIfObstructed(1);
        break;

    case Qt::Key_Left:
        setPos(pos() + QPointF(-distance,0));
        total_distance_moved -= distance;

        total_distance_moved -= MoveIfObstructed(-1);
        break;
    }
    if (total_distance_moved){
        MoveMessages(total_distance_moved);
    }

    QGraphicsItem::keyPressEvent(event);
}

void InstanceItem::MoveMessages(int amount)
{
    for (auto rect : rectangles){
        //moving sender message
        if ( rect->origin != nullptr){
            const QLineF& line = rect->origin->line();
            if (rect->origin->IsLeftToRight()){
                if (line.p1().x() > line.p2().x() + amount){
                    //transition L -> R
                    rect->origin->setLine(line.x1() - Rectangle::width, line.y1(), line.x2() + amount + Rectangle::width, line.y1());
                }
                else {
                    //moving on the right side
                    rect->origin->setLine(line.x1() , line.y1(), line.x2() + amount, line.y1());
                }
            }
            else {
                if (line.p2().x() + amount > line.p1().x() ){
                    //transition R -> L
                    rect->origin->setLine(line.x1() + Rectangle::width, line.y1(), line.x2() + amount - Rectangle::width, line.y1());
                }
                else {
                    //moving on the left side
                    rect->origin->setLine(line.x1(), line.y1(), line.x2() + amount, line.y1());
                }
            }
            rect->origin->update();
        }

        //moving returnal message
        if (rect->return_message){
            const QLineF& line = rect->return_message->line();
            if (rect->return_message->IsLeftToRight()){
                if (line.p1().x()  + amount > line.p2().x()){
                    //transition L -> R
                    rect->return_message->setLine(line.x1()  + amount  - Rectangle::width, line.y1(), line.x2()+ Rectangle::width, line.y1());
                }
                else {
                    //moving on the right side
                    rect->return_message->setLine(line.x1() + amount , line.y1(), line.x2(), line.y1());
                }
            }
            else {
                if (line.p2().x() > line.p1().x()  + amount){
                    //transition R -> L
                    rect->return_message->setLine(line.x1() + amount + Rectangle::width, line.y1(), line.x2()  - Rectangle::width, line.y1());
                }
                else {
                    //moving on the left side
                    rect->return_message->setLine(line.x1()  + amount, line.y1(), line.x2(), line.y1());
                }
            }
            rect->return_message->update();
        }

        //moving sent messages
        for (auto message : rect->sent){
            const QLineF& line = message->line();
            qDebug() << line.x1();
            if (message->IsLeftToRight()){
                if (line.x1() + amount > line.p2().x() ){
                    //transition L -> R
                    message->setLine(line.x1() - Rectangle::width  + amount, line.y1(), line.x2() + Rectangle::width, line.y1());
                }
                else {
                    //moving on the right side
                    message->setLine(line.x1()  + amount , line.y1(), line.x2(), line.y1());
                }
            }
            else {
                if (line.p2().x() > line.p1().x()  + amount ){
                    //transition R -> L
                    message->setLine(line.x1() + Rectangle::width  + amount , line.y1(), line.x2() - Rectangle::width, line.y1());
                }
                else {
                    //moving on the left side
                    message->setLine(line.x1()  + amount, line.y1(), line.x2(), line.y1());
                }
            }
            message->update();
        }

        //moving messages returned to the block
        for (auto message : rect->returning_messages){
            const QLineF& line = message->line();
            qDebug() << line.x1();
            if (message->IsLeftToRight()){
                if (line.x1() > line.p2().x() + amount ){
                    //transition L -> R
                    message->setLine(line.x1() - Rectangle::width, line.y1(), line.x2() + Rectangle::width + amount, line.y1());
                }
                else {
                    //moving on the right side
                    message->setLine(line.x1(), line.y1(), line.x2() + amount , line.y1() );
                }
            }
            else {
                if (line.p2().x() + amount > line.p1().x()  ){
                    //transition R -> L
                    message->setLine(line.x1() + Rectangle::width, line.y1(), line.x2() + amount - Rectangle::width, line.y1());
                }
                else {
                    //moving on the left side
                    message->setLine(line.x1(), line.y1(), line.x2() + amount, line.y1());
                }
            }
            message->update();
        }
    }
}



void InstanceItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}





