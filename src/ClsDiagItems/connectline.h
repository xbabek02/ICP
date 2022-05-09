#ifndef CONNECTLINE_H
#define CONNECTLINE_H

#include <QObject>
#include <QGraphicsLineItem>
#include "classdiagramitem.h"

class ConnectLine : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit ConnectLine(ClassDiagramItem *item1, ClassDiagramItem *item2,QObject *parent1 = nullptr, QGraphicsItem *parent2 = nullptr);
    ClassDiagramItem *item1;
    ClassDiagramItem *item2;

signals:

public slots:
    void FirstItemPosition(QPointF new_pos);
    void SecondItemPosition(QPointF new_pos);
};

#endif // CONNECTLINE_H
