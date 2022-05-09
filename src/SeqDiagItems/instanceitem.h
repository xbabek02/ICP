/**
 * @file instanceitem.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief QGraphicsItem instance of class diagram class
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef INSTANCEITEM_H
#define INSTANCEITEM_H

#include <QGraphicsItem>
#include <QMetaType>
#include <QPen>
#include "rectangle.h"
#include "./Entities/DiagramEntity.h"
#include "textitem_instance.h"
#include "idcls.h"
#include <QList>
#include <QString>
#include <QModelIndex>
#include <QObject>

class Rectangle;
class DiagramEntity;

class InstanceItem : public QGraphicsItem, public IDcls
{
public:
    // default statics
    static int default_x;
    static int default_y;
    static int default_length;
    static int default_width;
    static int distance;

    // class instance
    DiagramEntity *classEntity;

    // class display name
    QString text_class = "";

    // instance name
    QString text_name = "<unnamed>";

    // list of rectangles instance owns
    QList<Rectangle *> rectangles;

    /**
     * @brief Moves messages when instance was moved
     *
     * @param amount int value of moved distance
     */
    void MoveMessages(int amount);

    /**
     * @brief Finds the clear spot for an instance to stay at
     *
     * @param direction
     * @return int
     */
    int MoveIfObstructed(int direction = 1);
    bool visible = true;

    int length; // length of instance
    int width;  // width of instance

    TextItemInstance *ti = nullptr;

    /**
     * @brief Construct a new Instance Item object
     *
     * @param parent
     * @param classEntity class of the instance
     * @param text_class class text display value
     */
    InstanceItem(QGraphicsItem *parent = nullptr, DiagramEntity *classEntity = nullptr, QString text_class = "empty");

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const;

    /**
     * @brief Moving of instance by left and right arrow
     *
     * @param event
     */
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
};

Q_DECLARE_METATYPE(InstanceItem *)

#endif // INSTANCEITEM_H
