#include "connectline.h"
#include "classitemhead.h"
#include <QPen>
#include <QDebug>

ConnectLine::ConnectLine(ClassDiagramItem *item1, ClassDiagramItem *item2,
                         QObject *parent1, QGraphicsItem *parent2)
    : QObject(parent1), QGraphicsLineItem(parent2)
{
    //draws line
    setLine(item1->mainBody->x() + 50, item1->mainBody->y() + 5, item2->mainBody->x(), item2->mainBody->y());
    setPen(QPen{Qt::black, 3});
    setZValue(-500);

    this->item1 = item1;
    this->item2 = item2;

    //connects item body signal to this classes signals
    connect(item1->mainBody, SIGNAL(positionChange(QPointF)), this, SLOT(FirstItemPosition(QPointF)));
    connect(item2->mainBody, SIGNAL(positionChange(QPointF)), this, SLOT(SecondItemPosition(QPointF)));
}


//change line when item1 position changes
void ConnectLine::FirstItemPosition(QPointF new_pos)
{
    setLine(new_pos.x() + 50, new_pos.y() + 5, item2->mainBody->x() + 50, item2->mainBody->y() + 5);
}

//change line when item2 position changes
void ConnectLine::SecondItemPosition(QPointF new_pos)
{
    setLine(item1->mainBody->x() + 50, item1->mainBody->y() + 5, new_pos.x() + 50, new_pos.y() + 5);
}
