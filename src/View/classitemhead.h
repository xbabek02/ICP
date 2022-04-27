#ifndef CLASSITEMHEAD_H
#define CLASSITEMHEAD_H

#include <QGraphicsRectItem>
#include <QObject>

class ClassItemHead: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit ClassItemHead(QGraphicsRectItem *parent1 = nullptr, QObject *parent2 = nullptr);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void positionChange(QPointF pos);
};

#endif // CLASSITEMHEAD_H
