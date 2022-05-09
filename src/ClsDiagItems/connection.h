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
    explicit Connection(QGraphicsScene *scene, RelationEntity *entityModel, QGraphicsEllipseItem *node1, QGraphicsEllipseItem *node2, QObject *parent = nullptr);
    explicit Connection(QGraphicsScene *scene, RelationEntity *entityModel, QObject *parent = nullptr);
    ~Connection();
    void Rotate();
    void ChangeState();
    void DeleteThis();
    QGraphicsLineItem *GetMainLine();
    RelationEntity *GetModel();
    QGraphicsLineItem *mainLine;
    QPointF GetPosition1();
    QPointF GetPosition2();

signals:

public slots:
    void UpdateLine();
    void UpdateText(QString value);
    void CardinalityUpdate();

signals:
    void lineRotated();

private:
    RelationEntity *entityModel;
    TextStateItem *cardinality1;
    TextStateItem *cardinality2;
    QGraphicsEllipseItem *symbol;
    QPointF *position1;
    QPointF *position2;
    TextItem *name;
    QGraphicsLineItem *arrow1;
    QGraphicsLineItem *arrow2;
    QGraphicsEllipseItem *node1;
    QGraphicsEllipseItem *node2;
    int currentState;
    int numberOfStates;
    bool lock1;
    bool lock2;
    void UpdatePosition();
    void DrawSymbol(QGraphicsScene *scene);
    void CreateMainLine(QGraphicsScene *scene);
    void CreateArrow();
    void CreateSymbol();
    void CreateCardinalities();
    void LoadModel();

};

#endif // CONNECTION_H
