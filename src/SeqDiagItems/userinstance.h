/**
 * @file userinstance.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Special user instance, one for each sequence diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef USERINSTANCE_H
#define USERINSTANCE_H

#include "instanceitem.h"

class UserInstance : public InstanceItem
{
public:
    /**
     * @brief Construct a new User Instance object
     * 
     * @param parent 
     */
    UserInstance(QGraphicsItem *parent = nullptr);

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;
    QRectF boundingRect() const;
};

#endif // USERINSTANCE_H
