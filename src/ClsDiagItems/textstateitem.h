/**
 * @file textstateitem.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Text item with multiple states changing when being clicked
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TEXTSTATEITEM_H
#define TEXTSTATEITEM_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QFont>

class TextStateItem : public QGraphicsTextItem
{
    Q_OBJECT
public:
    /**
     * @brief TextStateItem is constructor
     * @param parent (optional)
     * @param id sets id of the item (optional)
     */
    explicit TextStateItem(QGraphicsItem *parent = nullptr, int id = 0);

    /**
     * @brief AddState adds new state
     * @param text sets name of the new state
     */
    void AddState(QString text);

    /**
     * @brief NextState increments current state
     */
    void NextState();

    /**
     * @brief UpdatePosition update the position based on the paraneter points
     * @param position1
     * @param position2
     */
    void UpdatePosition(QPointF *position1, QPointF *position2);

    /**
     * @brief FillCardinalities sets all the states on cardinality states
     */
    void FillCardinalities();

    /**
     * @brief FillAccess sets all the states on acceess states
     */
    void FillAccess();

    /**
     * @brief SetState
     * @param state is the number of required state
     */
    void SetState(int state);

    /**
     * @brief GetState
     * @return number of current state
     */
    int GetState();

    /**
     * @brief GetID
     * @return id of the object
     */
    int GetID();

protected:
    /**
     * @brief mousePressEvent emits stateChangeSignal
     * @param event
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    /**
     * @brief textStates
     */
    QList<QString> textStates;

    /**
     * @brief currentState
     */
    int currentState;

    /**
     * @brief numberOfStates
     */
    int numberOfStates;

    /**
     * @brief id
     */
    int id;

signals:
    /**
     * @brief emits when state changed
     * @param id of the object
     */
    void stateChange(int id);
};

#endif // TEXTSTATEITEM_H
