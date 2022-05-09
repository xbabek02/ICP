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

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include "classdiagramitem.h"
#include "textstateitem.h"
#include "textitem.h"
#include "../Entities/RelationEntity.h"
#include "../Common/enums.h"

class RelationEntity;
class ClassDiagramItem;

//nazvy vztahu, relacni entity, custom lajny

class Connection : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Connection is constructor for creating brand new connection
     * @param scene is graphics scene
     * @param entityModel is model of this object
     * @param node1 is node of the first object
     * @param node2 is node of the second object
     * @param parent
     */
    explicit Connection(QGraphicsScene *scene, RelationEntity *entityModel, QGraphicsEllipseItem *node1, QGraphicsEllipseItem *node2, QObject *parent = nullptr);

    /**
     * @brief Connection is constructor for loading from file
     * @param scene is graphics scene
     * @param entityModel if model which is to be loaded
     * @param parent
     */
    explicit Connection(QGraphicsScene *scene, RelationEntity *entityModel, QObject *parent = nullptr);
    ~Connection();

    /**
     * @brief Rotate rotated the line
     */
    void Rotate();

    /**
     * @brief ChangeState chenged type of the line
     */
    void ChangeState();

    /**
     * @brief DeleteThis object delets itself
     */
    void DeleteThis();

    /**
     * @brief GetMainLine
     * @return return main line
     */
    QGraphicsLineItem *GetMainLine();

    /**
     * @brief GetModel
     * @return model of the object
     */
    RelationEntity *GetModel();

    /**
     * @brief mainLine
     */
    QGraphicsLineItem *mainLine;

    /**
     * @brief GetPosition1
     * @return position of node1
     */
    QPointF GetPosition1();

    /**
     * @brief GetPosition2
     * @return position of node2
     */
    QPointF GetPosition2();

public slots:
    /**
     * @brief UpdateLine updates position of the line
     */
    void UpdateLine();

    /**
     * @brief UpdateText sets name of the relation
     * @param value if the new name
     */
    void UpdateText(QString value);

    /**
     * @brief CardinalityUpdate updates cardinality values
     */
    void CardinalityUpdate();

signals:
    /**
     * @brief lineRotated emits when line of rotated
     */
    void lineRotated();

private:
    /**
     * @brief entityModel is model of this object
     */
    RelationEntity *entityModel;

    /**
     * @brief cardinality1
     */
    TextStateItem *cardinality1;

    /**
     * @brief cardinality2
     */
    TextStateItem *cardinality2;

    /**
     * @brief symbol is the symbol for indication type of the line
     */
    QGraphicsEllipseItem *symbol;

    /**
     * @brief position1
     */
    QPointF *position1;

    /**
     * @brief position2
     */
    QPointF *position2;

    /**
     * @brief name
     */
    TextItem *name;

    /**
     * @brief arrow1
     */
    QGraphicsLineItem *arrow1;

    /**
     * @brief arrow2
     */
    QGraphicsLineItem *arrow2;

    /**
     * @brief node1
     */
    QGraphicsEllipseItem *node1;

    /**
     * @brief node2
     */
    QGraphicsEllipseItem *node2;

    /**
     * @brief currentState
     */
    int currentState;

    /**
     * @brief numberOfStates
     */
    int numberOfStates;

    /**
     * @brief lock1
     */
    bool lock1;

    /**
     * @brief lock2
     */
    bool lock2;

    /**
     * @brief UpdatePosition updates position of the line
     */
    void UpdatePosition();

    /**
     * @brief DrawSymbol draws the symbol
     * @param scene
     */
    void DrawSymbol(QGraphicsScene *scene);

    /**
     * @brief CreateMainLine draws the main line
     * @param scene
     */
    void CreateMainLine(QGraphicsScene *scene);

    /**
     * @brief CreateArrow draws the arrow for the generalization
     */
    void CreateArrow();

    /**
     * @brief CreateSymbol creates the arrow
     */
    void CreateSymbol();

    /**
     * @brief CreateCardinalities
     */
    void CreateCardinalities();

    /**
     * @brief LoadModel
     */
    void LoadModel();

};

#endif // CONNECTION_H
