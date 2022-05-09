/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Custom QGraphicsScene, takes responsibility of click and key press events
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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
    /**
     * @brief Construct a new Sequence diagram scene, 
     * 
     * @param mm Method model to be refreshed when message is selected
     * @param parent QObject parent instance
     */
    explicit SeqDScene(MethodModel *mm, QObject *parent = nullptr);

    /**
     * @brief Deletes Rectangle and all related items to it from the scene
     * 
     * @param rectangle 
     */
    void DeleteRectangle(Rectangle *rectangle);

    /**
     * @brief Deletes message and all related items to it from the scene
     * 
     * @param message 
     */
    void DeleteMessage(MessageItem *message);

    /**
     * @brief Get the all dependent objects to the rectangle
     * 
     * @param rectangle 
     * @param list output list of dependent objects
     */
    void GetAllDependent(Rectangle *rectangle, QList<QGraphicsItem *> *list);

    /**
     * @brief Get the all the dependent objects of rectangle but the rectangles, that belong to
     * specified rectangles owner instance, used for visibility dependency
     * 
     * @param rectangle 
     * @param list output list of dependent objects
     */
    void GetAllDependentRectFree(Rectangle *rectangle, QList<QGraphicsItem *> *list);
    
    /**
     * @brief Get the all the dependent objects of instance but the rectangles, that belong to
     * the instance
     * @param instance 
     * @return QList<QGraphicsItem *>* 
     */
    QList<QGraphicsItem *> *GetAllDependentOwnRectFree(InstanceItem *instance);

    /**
     * @brief Get the all dependent objects to the instance
     * 
     * @param instance 
     * @return QList<QGraphicsItem *>* 
     */
    QList<QGraphicsItem *> *GetAllDependent(InstanceItem *instance);

    /**
     * @brief Counts the rectangles at cursor position
     * 
     * @param position 
     * @return int count
     */
    int CountRectanglesAtCursor(QPointF position);
public slots:
    /**
     * @brief Called if selection is changed
     * 
     */
    void selChanged();

protected:
    /**
     * @brief Mouse events for creating arrows by click and drag
     * 
     * @param event QGraphicsSceneMouseEvent
     */
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

private:
    MessageItem *editedMessage = nullptr;
    MethodModel *mm;
};

#endif // SEQDSCENE_H
