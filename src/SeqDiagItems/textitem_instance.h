/**
 * @file textitem_instance.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
* @brief Text field of instance to be edited/editable
 * @version 0.1
 * @date 2022-05-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef TEXTITEM_INSTANCE_H
#define TEXTITEM_INSTANCE_H

#include <QObject>
#include <QGraphicsTextItem>
#include "idcls.h"

class TextItemInstance : public QGraphicsTextItem, public IDcls
{
    Q_OBJECT

public:
    explicit TextItemInstance(QGraphicsItem  *parent = nullptr);
    void setText(QString value);
    void SetId(int id);
    void SetLock(bool lock);
    int GetId();

protected:
    virtual void keyReleaseEvent(QKeyEvent * event) override;

private:
    int id;

signals:
    void valueChanged(QString value);

};

#endif // TEXTITEM_INSTANCE_H
