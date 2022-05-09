/**
 * @file rectangle.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief QGraphicsItem rectangle class
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QGraphicsRectItem>
#include <QList>
#include "messageitem.h"
#include "instanceitem.h"
#include "idcls.h"
#include "itemvisibility.h"

class MessageItem;
class InstanceItem;

class Rectangle : public QGraphicsRectItem, public IDcls, public ItemVisibility
{
private:
    int length;

public:
    // statics
    static int width;
    static int min_length;
    static Rectangle *initial_block;
    static int colision_offset;

    // parameters
    bool nested = false;
    int vertical_offset;
    int addedLength;

    /**
     * @brief Get the added + computed length of an object
     *
     * @return int
     */
    int GetLength();

    /**
     * @brief Set the Base of object
     *
     * @param length
     */
    void SetBaseLength(int length);

    /**
     * @brief Update the rectangle and its computed length
     *
     */
    void UpdateRectangle();

    /**
     * @brief Adds value to the added length, resulted added length cannot be negative
     *
     * @param added
     */
    void AddRemoveLength(int added);

    /**
     * @brief Updates all the lengths of rectangles
     *
     */
    static void UpdateLengths();

    /**
     * @brief Updates returnal messages
     *
     */
    void UpdateReturnal();

    /**
     * @brief Get the End Of Block object in scenePos coordinates
     *
     * @return int y value
     */
    int GetEndOfBlock();

    /**
     * @brief Get the Start Of Block object in scenePos coordinates
     *
     * @return int y value
     */
    int GetStartOfBlock();

    /**
     * @brief Construct a new Rectangle object
     *
     * @param parent
     * @param origin message creating the rectangle
     * @param vertical_offset
     */
    Rectangle(QGraphicsItem *parent = nullptr, MessageItem *origin = nullptr, int vertical_offset = 20);

    void AddMessage(MessageItem *);

    // messages
    MessageItem *origin = nullptr;
    MessageItem *return_message = nullptr;
    QList<MessageItem *> returning_messages; // messages returning back to the block
    QList<MessageItem *> sent;
    InstanceItem *instance = nullptr;

protected:
    /**
     * @brief Recursive function for updating lengths of rectangles
     *
     * @return int
     */
    int UpdateLengthsRec();

    virtual void update(const QRectF &rect = QRectF());
};

#endif // RECTANGLE_H
