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
    static int default_x;
    static int default_y;
    static int default_length;
    static int default_width;
    static int distance;
    DiagramEntity*classEntity;
    QString text_class = "";
    QString text_name = "<unnamed>";
    QList<Rectangle*> rectangles;
    void MoveMessages(int amount);
    int MoveIfObstructed(int direction = 1);
    bool visible = true;

    int length;
    int width;

    TextItemInstance *ti = nullptr;
    InstanceItem(QGraphicsItem *parent = nullptr, DiagramEntity*classEntity = nullptr, QString text_class = "empty");

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override ;
    QRectF boundingRect() const;
    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:

};

Q_DECLARE_METATYPE(InstanceItem*)

#endif // INSTANCEITEM_H
