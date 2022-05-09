#ifndef CLASSITEMHEAD_H
#define CLASSITEMHEAD_H

#include <QGraphicsRectItem>
#include <QObject>

class ClassItemHead: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    QRectF boundingRect() const override;
    explicit ClassItemHead(int width, int height, QGraphicsRectItem *parent1 = nullptr, QObject *parent2 = nullptr);
    void SetWidth(int value);
    void SetHeight(int value);
    void EmitPositionSignal();

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    int width;
    int height;

signals:
    void positionChange(QPointF pos);
    void mouseReleaseSignal(QPointF position);
};

#endif // CLASSITEMHEAD_H
