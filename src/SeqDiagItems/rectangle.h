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
    static int width;
    static int min_length;
    static Rectangle*initial_block;
    static int colision_offset;
    QList<MessageItem*> sent;
    bool nested = false;
    int vertical_offset;
    int addedLength;
    int GetLength();
    void SetBaseLength(int length);
    void UpdateRectangle();
    void AddRemoveLength(int added);
    static void UpdateLengths();
    void UpdateReturnal();

    int GetEndOfBlock();
    int GetStartOfBlock();

    Rectangle(QGraphicsItem *parent = nullptr, MessageItem*origin = nullptr, int vertical_offset = 20);

    void AddMessage(MessageItem*);

    MessageItem*origin = nullptr;
    MessageItem*return_message = nullptr;
    QList<MessageItem*> returning_messages; //messages returning back to the block
    InstanceItem*instance = nullptr;


protected:

    int UpdateLengthsRec();
    virtual void update(const QRectF &rect = QRectF());
    //virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // RECTANGLE_H
