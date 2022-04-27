#ifndef CLASSDIAGRAMITEM_H
#define CLASSDIAGRAMITEM_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "classitemhead.h"

class ClassDiagramItem : public QObject
{
    Q_OBJECT

public:
    ClassDiagramItem(QGraphicsScene *scene, QObject *parent1 = nullptr);
    void AddRow();
    void RemoveRow();
    ClassItemHead *mainBody;

signals:
    void PositionSignal(QPointF position);

private:
    QList<QGraphicsRectItem*> rows;
    QList<QGraphicsTextItem*> texts;
    int numberOfRows;
};

#endif // CLASSDIAGRAMITEM_H
