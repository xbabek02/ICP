/**
 * @file clasitemhead.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief main part of the class diagram object, parent of all graphics items
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CLASSITEMHEAD_H
#define CLASSITEMHEAD_H

#include <QGraphicsRectItem>
#include <QObject>

class ClassItemHead: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    /**
     * @brief boundingRect sets bounding rectangle of the whole class object
     * @return bounding ractangle
     */
    QRectF boundingRect() const override;

    /**
     * @brief ClassItemHead is constructor
     * @param width sets starting width of the object
     * @param height sets starting height of the object
     * @param parent1 is QGraphicsRectItem parent (optinal)
     * @param parent2 is QObject parent (optional)
     */
    explicit ClassItemHead(int width, int height, QGraphicsRectItem *parent1 = nullptr, QObject *parent2 = nullptr);

    /**
     * @brief SetWidth
     * @param value is the new width
     */
    void SetWidth(int value);

    /**
     * @brief SetHeight
     * @param value is the height
     */
    void SetHeight(int value);

    /**
     * @brief EmitPositionSignal is method for emiting the position signal
     * needed in special cases
     */
    void EmitPositionSignal();

protected:
    /**
     * @brief mouseMoveEvent emits positionChange signal when mouse moves
     * with this object
     * @param event
     */
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    /**
     * @brief mouseReleaseEvent emits signal which is needed for creating
     * position history of the class object
     * @param event
     */
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    /**
     * @brief itemChange emits positionChange signal when this object changed
     * @param change
     * @param value
     * @return
     */
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

private:
    /**
     * @brief width
     */
    int width;
    /**
     * @brief height
     */
    int height;

signals:
    /**
     * @brief positionChange emits when position of the object changed
     * @param pos is the new position
     */
    void positionChange(QPointF pos);

    /**
     * @brief mouseReleaseSignal emits position when mouse releases on this object
     * @param position
     */
    void mouseReleaseSignal(QPointF position);
};

#endif // CLASSITEMHEAD_H
