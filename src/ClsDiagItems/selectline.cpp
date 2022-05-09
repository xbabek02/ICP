#include "selectline.h"

SelectLine::SelectLine(int x1, int y1, int x2, int y2, QGraphicsItem *parent1, QObject *parent2) : QObject(parent2), QGraphicsLineItem(parent1)
{
    setLine(x1, y1, x2, y2);
    setPen(QPen{Qt::black,3});
    selectChain = false;
}

QVariant SelectLine::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (value == true && selectChain == false)
            emit selectChange(true);
        else if(value == false && selectChain == false)
            emit selectChange(false);
    }

    if(selectChain == true)
        selectChain = false;

    return QGraphicsItem::itemChange(change, value);
}

void SelectLine::SetSelectChain()
{
    selectChain = true;
}
