#ifndef TEXTSTATEITEM_H
#define TEXTSTATEITEM_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QFont>

class TextStateItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    explicit TextStateItem(QGraphicsItem *parent = nullptr, int id = 0);
    void AddState(QString text);
    void NextState();
    void UpdatePosition(QPointF *position1, QPointF *position2);
    void FillCardinalities();
    void FillAccess();
    void SetState(int state);
    int GetState();
    int GetID();

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QList<QString> textStates;
    int currentState;
    int numberOfStates;
    int id;

signals:
    void stateChange(int id);
};

#endif // TEXTSTATEITEM_H
