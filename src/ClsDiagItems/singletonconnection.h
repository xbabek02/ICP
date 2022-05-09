/**
 * @file singletonconnection.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Main graphics class for singleton connection
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SINGLETONCONNECTION_H
#define SINGLETONCONNECTION_H

#include <QObject>
#include "classdiagramitem.h"
#include <QGraphicsLineItem>
#include "selectline.h"
#include "../Entities/RelationEntity.h"
#include "../Common/enums.h"

class ClassDiagramItem;
class RelationEntity;

class SingletonConnection : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief SingletonConnection is constructor
     * @param item is pointer to the class item
     * @param node1 is the starting node of the item
     * @param node2 is the ending node
     * @param entityModel is the model of the relation
     * @param parent (optional)
     */
    explicit SingletonConnection(ClassDiagramItem *item, QGraphicsEllipseItem *node1,
                                 QGraphicsEllipseItem *node2, RelationEntity *entityModel, QObject *parent = nullptr);

    /**
     * @brief SetDistance sets distance form the item center
     * @param value
     */
    void SetDistance(int value);

    /**
     * @brief GetDistance
     * @return current distance form item center
     */
    int GetDistance();

    /**
     * @brief ChangeState changed type of line
     */
    void ChangeState();

    /**
     * @brief GetMainLine
     * @return pointer to the main line
     */
    QGraphicsLineItem *GetMainLine();

    /**
     * @brief GetModel
     * @return pointer to the relation model
     */
    RelationEntity *GetModel();

    ~SingletonConnection();

private:
    /**
     * @brief distance
     */
    int distance;

    /**
     * @brief ChangeNodes switches the nodes, sometimes neeeded
     */
    void ChangeNodes();

    /**
     * @brief Delete deletes the lines, needed when redraw
     */
    void Delete();

    /**
     * @brief Draw draws the line
     */
    void Draw();

    /**
     * @brief DrawSymbol draws symbol which indicates type of the relation
     * @param update is false when symbol is drawn for the first time
     */
    void DrawSymbol(bool update);

    /**
     * @brief DrawArrow draw arrow of the generalization
     * @param update is false when arrow is drawn for the first time
     */
    void DrawArrow(bool update);

    /**
     * @brief DrawText
     * @param update is false when text is drawn for the first time
     */
    void DrawText(bool update);

    /**
     * @brief HorizontalLine draws line when nodes are in horizontal line
     * @return list of created lines
     */
    QList<SelectLine*> HorizontalLine();

    /**
     * @brief HorizontalLine draws line when nodes are in horizontal line
     * @return list of created lines
     */
    QList<SelectLine*> VerticalLine();

    /**
     * @brief HorizontalLine draws line when nodes are in vertical line
     * @return list of created lines
     */
    QList<SelectLine*> NarrowLine();

    /**
     * @brief HorizontalLine draws line when nodes are in narrow line
     * @return list of created lines
     */
    QList<SelectLine*> Slant();

    /**
     * @brief HorizontalLine draws line when nodes are in slant line
     * @return list of created lines
     */
    ClassDiagramItem *item;

    /**
     * @brief node1
     */
    QGraphicsEllipseItem *node1;

    /**
     * @brief node2
     */
    QGraphicsEllipseItem *node2;

    /**
     * @brief lines
     */
    QList<SelectLine*> lines;

    /**
     * @brief symbol
     */
    QGraphicsEllipseItem *symbol;

    /**
     * @brief arrowPoint
     */
    QPointF arrowPoint;

    /**
     * @brief currentState
     */
    int currentState;

    /**
     * @brief numberOfStates
     */
    int numberOfStates;

    /**
     * @brief cardinality1
     */
    TextStateItem *cardinality1;

    /**
     * @brief cardinality2
     */
    TextStateItem *cardinality2;

    /**
     * @brief arrow1
     */
    QGraphicsLineItem *arrow1;

    /**
     * @brief arrow2
     */
    QGraphicsLineItem *arrow2;

    /**
     * @brief text
     */
    QGraphicsTextItem *text;

    /**
     * @brief entityModel
     */
    RelationEntity *entityModel;

    /**
     * @brief PutCardinalities
     * @param update
     */
    void PutCardinalities(bool update);

    /**
     * @brief GetLineMidPoint
     * @param line
     * @param divide is 2 when exact middle is required
     * @return gets middle point of the line
     */
    QPointF GetLineMidPoint(QGraphicsLineItem *line, double divide);

public slots:
    /**
     * @brief Update updates all the data and graphic items
     */
    void Update();
    /**
     * @brief Select selects all the lines when one line is selected
     * @param selected
     */
    void Select(bool selected);

    /**
     * @brief ModelUpdate updates data in the model
     */
    void ModelUpdate();

    /**
     * @brief CardinalityUpdate updates cardinalities
     */
    void CardinalityUpdate();

};

#endif // SINGLETONCONNECTION_H
