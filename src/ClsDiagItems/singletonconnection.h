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
    explicit SingletonConnection(ClassDiagramItem *item, QGraphicsEllipseItem *node1,
                                 QGraphicsEllipseItem *node2, RelationEntity *entityModel, QObject *parent = nullptr);
    void SetDistance(int value);
    int GetDistance();
    void ChangeState();
    QGraphicsLineItem *GetMainLine();
    RelationEntity *GetModel();
    ~SingletonConnection();

private:
    int distance;
    void ChangeNodes();
    void Delete();
    void Draw();
    void DrawSymbol(bool update);
    void DrawArrow(bool update);
    void DrawText(bool update);
    QList<SelectLine*> HorizontalLine();
    QList<SelectLine*> VerticalLine();
    QList<SelectLine*> NarrowLine();
    QList<SelectLine*> Slant();
    ClassDiagramItem *item;
    QGraphicsEllipseItem *node1;
    QGraphicsEllipseItem *node2;
    QList<SelectLine*> lines;
    QGraphicsEllipseItem *symbol;
    QPointF arrowPoint;
    int currentState;
    int numberOfStates;
    TextStateItem *cardinality1;
    TextStateItem *cardinality2;
    QGraphicsLineItem *arrow1;
    QGraphicsLineItem *arrow2;
    QGraphicsTextItem *text;
    RelationEntity *entityModel;
    void PutCardinalities(bool update);
    QPointF GetLineMidPoint(QGraphicsLineItem *line, double divide);

public slots:
    void Update();
    void Select(bool selected);
    void ModelUpdate();
    void CardinalityUpdate();

};

#endif // SINGLETONCONNECTION_H
