/**
 * @file classdiagramitem.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Main graphics item for class object in class diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CLASSDIAGRAMITEM_H
#define CLASSDIAGRAMITEM_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "classitemhead.h"
#include <string>
#include <QDebug>
#include <cmath>
#include <QPainter>
#include "textitem.h"
#include "textstateitem.h"
#include <QGraphicsItemGroup>
#include "../Entities/DiagramEntity.h"
#include "../Entities/AttributeEntity.h"
#include "../Common/enums.h"
#include "connection.h"
#include <qundostack.h>
#include "../ClassDiagramCommands/classmovecommand.h"

class DiagramEntity;
class AttributeEntity;
class Connection;
class SingletonConnection;

class ClassDiagramItem : public QObject
{
    Q_OBJECT
    Q_INTERFACES()

public:
    explicit ClassDiagramItem(QGraphicsScene *scene, DiagramEntity *entityModel, QObject *parent = nullptr);
    ~ClassDiagramItem();

    /**
     * method for creating new row (attribute/method) for the class
     * sets the implicit name of the attribute
     * @param color sets the color of the row
     */
    void NewRow(QColor color);

    /**
     * method for adding a row in the class
     * @param textValue sets the name of the attribute
     * @param color sets the color of the row
     */
    void AddRow(QString textValue, QColor color);

    /**
     * text item for the name of the class
     */
    TextItem *text;

    /**
     * removes last added row
     */
    void RemoveRow();

    /**
     * decrements methodRowIndex, which results in adding one
     * method and removing one attribute
     */
    void PushMethodUp();

    /**
     * increments methodRowIndex, which results in removing one method
     * and adding one attribute
     */
    void PushMethodDown();

    /**
     * setter for undoStack
     * @param undoStack
     */
    void SetUndoStack(QUndoStack *undoStack);

    /**
     * return id of the node
     * @param node whose id will be returned
     * @return id of the parameter node
     */
    int GetNodeID(QGraphicsEllipseItem *node);

    /**
     * updates the class name
     * @param name is the new name
     */
    void ModelNameChanged(QString name);

    /**
     * returns current height of the graphics object.
     * @return height of the object
     */
    int GetHeight();

    /**
     * returns current width of the graphics object
     * @return width of the object
     */

    int GetWidth();

    /**
     * sets position to the last known position
     * used for undo move
     */
    void LastPosition();

    /**
     * @brief SetWidth sets graphics object width
     * @param value
     */
    void SetWidth(int value);

    /**
     * @brief GetMainBody
     * @return pointer to the main graphics object parent
     */
    ClassItemHead *GetMainBody();

    /**
     * @brief GetModel
     * @return pointer to the model object
     */
    DiagramEntity *GetModel();

    /**
     * @brief GetCenter
     * @return point in the center of the object
     */
    QPointF *GetCenter();

    /**
     * @brief GetLinePoint
     * @param destination
     * @return position of node which is the closest to the destination point
     */
    QPointF *GetLinePoint(QPointF *destination);

    /**
     * @brief GetNode
     * @param id of the node
     * @return node which has parameter id
     */
    QGraphicsEllipseItem *GetNode(int id);

    /**
     * @brief GetRelationViewItems
     * @return list of views of relations of the object
     */
    QList<Connection*> GetRelationViewItems();


signals:
    /**
     * @brief PositionSignal signal which is emited when
     * position of the object changed
     * @param position is the new position
     */
    void PositionSignal(QPointF position);

    /**
     * @brief rowChangeSignal is signals which is emited
     * when text of the row changed
     */
    void rowChangeSignal();

    /**
     * @brief moveUndoSignal is emited when move undo is called
     * @param thisObject
     */
    void moveUndoSignal(ClassDiagramItem *thisObject);

public slots:
    /**
     * @brief RowChanged processes changed of text change in to row
     * displays new value
     * @param value is new text value
     * @param id of the row
     */
    void RowChanged(QString value, int id);

    /**
     * @brief PositionChange processes change of the position
     * @param pos is new position
     */
    void PositionChange(QPointF pos);

    /**
     * @brief NameChanged processes change of the class name
     * @param value if the new name
     */
    void NameChanged(QString value);

    /**
     * @brief AccessUpdate processes any row's access change
     * @param id is id of the row
     */
    void AccessUpdate(int id);

    /**
     * @brief SetLastPosition appends new position in the
     * list of position history
     * @param position
     */
    void SetLastPosition(QPointF position);

private:
    /**
     * @brief AddNode creates new node
     * @param position is position of the node
     */
    void AddNode(QPointF position);

    /**
     * @brief UpdateNodes updates layout of the nodes depending on
     * the object's size
     */
    void UpdateNodes();

    /**
     * @brief CreateNodes creates all nodes and sets implicit positions
     */
    void CreateNodes();

    /**
     * @brief LoadModel loads data from model into the object
     */
    void LoadModel();

    /**
     * @brief Check checks validity of arguments and methods
     */
    void Check();

    /**
     * @brief PointDistance
     * @param point1
     * @param point2
     * @return distance between two points
     */
    double PointDistance(QPointF point1, QPointF point2);

    /**
     * @brief positionHistory is list of all past positions
     */
    QList<QPointF> positionHistory;

    /**
     * @brief rows -> rectangle objects
     */
    QList<QGraphicsRectItem*> rows;

    /**
     * @brief names of atributes and methods
     */
    QList<QGraphicsTextItem*> texts;

    /**
     * @brief accesses
     */
    QList<TextStateItem*> accesses;

    /**
     * @brief nodes
     */
    QList<QGraphicsEllipseItem*> nodes;

    /**
     * @brief entityModel is model of the object
     */
    DiagramEntity *entityModel;

    /**
     * @brief classNameText is name of the class
     */
    QString classNameText;

    /**
     * @brief mainBody is main graphics item parent of the whole object
     */
    ClassItemHead *mainBody;

    /**
     * @brief undoStack
     */
    QUndoStack *undoStack;

    /**
     * @brief numberOfRows
     */
    int numberOfRows;

    /**
     * @brief methodRowIndex
     */
    int methodRowIndex;

    /**
     * @brief width
     */
    int width;
};

#endif // CLASSDIAGRAMITEM_H
