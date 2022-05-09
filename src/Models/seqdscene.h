#ifndef SEQDSCENE_H
#define SEQDSCENE_H

#include <QGraphicsScene>
#include "./SeqDiagItems/messageitem.h"
#include "./SeqDiagItems/rectangle.h"
#include "./SeqDiagItems/instanceitem.h"
#include "methodmodel.h"
#include <QList>

class SeqDScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SeqDScene(MethodModel*mm, QObject*parent = nullptr);
    void DeleteRectangle(Rectangle*rectangle);
    void DeleteMessage(MessageItem*message);
    void GetAllDependent(Rectangle*rectangle, QList<QGraphicsItem*>*list);
    QList<QGraphicsItem *> *GetAllDependent(InstanceItem*instance);

public slots:
    void selChanged();

protected:

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event);

private:
    MessageItem*editedMessage = nullptr;
    MethodModel*mm;

};

#endif // SEQDSCENE_H
