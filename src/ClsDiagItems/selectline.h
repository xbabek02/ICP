#ifndef SELECTLINE_H
#define SELECTLINE_H

#include <QGraphicsLineItem>
#include <QPen>
#include <QObject>

class SelectLine : public QObject, public QGraphicsLineItem
{
    Q_OBJECT

public:
    SelectLine(int x1, int y1, int x2, int y2, QGraphicsItem *parent1 = nullptr, QObject *parent2 = nullptr);
    void SetSelectChain();

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    bool selectChain;

signals:
    void selectChange(bool selected);
};

#endif // SELECTLINE_H
