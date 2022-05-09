/**
 * @file seqdscene.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "connection.h"
#include <QVector2D>

#define NUMBER_OF_STATES 4
#define LINE_Z_VALUE -500
#define LINE_THICKNESS 3

Connection::Connection(QGraphicsScene *scene, RelationEntity *entityModel, QObject *parent)
    : QObject(parent)
{
    this->entityModel = entityModel;
    this->entityModel->SetThisViewItem(this);
    std::pair<DiagramEntity*, DiagramEntity*> entities = entityModel->GetEntites();
    node1 = entities.first->GetDiagramItem()->GetNode(entityModel->GetNode1());
    node2 = entities.second->GetDiagramItem()->GetNode(entityModel->GetNode2());

    UpdatePosition();
    CreateMainLine(scene);
    CreateCardinalities();
    CreateArrow();
    CreateSymbol();

    cardinality1->SetState(static_cast<int>(entityModel->GetCardinalities().first));
    cardinality2->SetState(static_cast<int>(entityModel->GetCardinalities().second));

    name = new TextItem;
    name->setPlainText(QString::fromStdString(entityModel->GetName()));
    scene->addItem(name);

    //connects item body signal to this classes signals
    connect(dynamic_cast<ClassItemHead*>(node1->parentItem()), SIGNAL(positionChange(QPointF)), this, SLOT(UpdateLine()));
    connect(dynamic_cast<ClassItemHead*>(node2->parentItem()), SIGNAL(positionChange(QPointF)), this, SLOT(UpdateLine()));
    connect(name, SIGNAL(valueChanged(QString,int)), this, SLOT(UpdateText(QString)));
    connect(this, SIGNAL(lineRotated()), this, SLOT(UpdateLine()));
    connect(cardinality1, SIGNAL(stateChange(int)), this, SLOT(CardinalityUpdate()));
    connect(cardinality2, SIGNAL(stateChange(int)), this, SLOT(CardinalityUpdate()));

    numberOfStates = NUMBER_OF_STATES;
    currentState = static_cast<int>(entityModel->GetType()) - 1;
    ChangeState();
    UpdateLine();

    if(entityModel->GetSide() == Enums::RelationSide::second)
    {
        Rotate();
        entityModel->SwitchRelationSide();
    }
}

Connection::Connection(QGraphicsScene *scene, RelationEntity *entityModel, QGraphicsEllipseItem *node1, QGraphicsEllipseItem *node2, QObject *parent)
    : QObject(parent)
{
    this->entityModel = entityModel;
    this->entityModel->SetThisViewItem(this);
    this->node1 = node1;
    this->node2 = node2;


    UpdatePosition();
    CreateMainLine(scene);
    CreateCardinalities();
    CreateArrow();
    CreateSymbol();

    name = new TextItem;
    name->setPlainText(QString::fromStdString(entityModel->GetName()));
    scene->addItem(name);


    //connects item body signal to this classes signals
    connect(dynamic_cast<ClassItemHead*>(node1->parentItem()), SIGNAL(positionChange(QPointF)), this, SLOT(UpdateLine()));
    connect(dynamic_cast<ClassItemHead*>(node2->parentItem()), SIGNAL(positionChange(QPointF)), this, SLOT(UpdateLine()));
    connect(name, SIGNAL(valueChanged(QString,int)), this, SLOT(UpdateText(QString)));
    connect(this, SIGNAL(lineRotated()), this, SLOT(UpdateLine()));
    connect(cardinality1, SIGNAL(stateChange(int)), this, SLOT(CardinalityUpdate()));
    connect(cardinality2, SIGNAL(stateChange(int)), this, SLOT(CardinalityUpdate()));

    numberOfStates = NUMBER_OF_STATES;
    currentState = 1;
    ChangeState();

    UpdateLine();
}

void Connection::LoadModel()
{
}

void Connection::CreateArrow()
{
    arrow1 = new QGraphicsLineItem(mainLine);
    arrow2 = new QGraphicsLineItem(mainLine);

    arrow1->setPen(QPen{Qt::black, LINE_THICKNESS});
    arrow2->setPen(QPen{Qt::black, LINE_THICKNESS});
    arrow1->setVisible(false);
    arrow2->setVisible(false);
}

void Connection::CreateMainLine(QGraphicsScene *scene)
{
    mainLine = scene->addLine(this->position1->x(), this->position1->y(), this->position2->x(), this->position2->y());
    mainLine->setPen(QPen{Qt::black, LINE_THICKNESS});
    mainLine->setZValue(LINE_Z_VALUE);
    mainLine->setFlag(QGraphicsItem::ItemIsSelectable);
}

void Connection::CreateSymbol()
{
    this->symbol = new QGraphicsEllipseItem(mainLine);
    this->symbol->setBrush(QBrush{Qt::black});
    this->symbol->setRect(this->position1->x() - 10, this->position1->y() - 10, 20, 20);
    this->symbol->setPen(QPen{Qt::black, 3});
    symbol->setZValue(-10);
}

RelationEntity *Connection::GetModel()
{
    return entityModel;
}

void Connection::CreateCardinalities()
{
    cardinality1 = new TextStateItem(mainLine);
    cardinality2 = new TextStateItem(mainLine);

    cardinality1->FillCardinalities();
    cardinality2->FillCardinalities();
}

void Connection::UpdatePosition()
{
    position1 = new QPointF(node1->x() + node1->parentItem()->x(), node1->y() + node1->parentItem()->y());
    position2 = new QPointF(node2->x() + node2->parentItem()->x(), node2->y() + node2->parentItem()->y());
}

//change line when item1 position changes
void Connection::UpdateLine()
{
    UpdatePosition();

    double deltaX {(position1->x() - position2->x())/5};
    double deltaY {(position1->y() - position2->y())/5};

    mainLine->setLine(this->position1->x(), this->position1->y(), this->position2->x(), this->position2->y());

    symbol->setRect(this->position1->x() - 10 - deltaX, this->position1->y() - 10 - deltaY, 20, 20);

    cardinality1->UpdatePosition(this->position1, this->position2);
    cardinality2->UpdatePosition(this->position2, this->position1);

    name->setPos((this->position1->x() + this->position2->x())/2, (this->position1->y() + this->position2->y())/2);

    QVector2D *vector = new QVector2D(deltaX, deltaY);
    vector->normalize();
    *vector = *vector * 20;

    arrow1->setLine(position1->x(), position1->y(), position1->x() - vector->y() - vector->x(), position1->y() + vector->x() - vector->y());
    arrow2->setLine(position1->x(), position1->y(), position1->x() + vector->y() - vector->x(), position1->y() - vector->x() - vector->y());

    delete vector;
}

void Connection::Rotate()
{
    auto tmpNode = node1;
    node1 = node2;
    node2 = tmpNode;
    entityModel->SwitchRelationSide();
    emit lineRotated();
}

void Connection::ChangeState()
{
    currentState = (currentState + 1) % numberOfStates;
    switch(currentState)
    {
        case 0:
            arrow1->setVisible(false);
            arrow2->setVisible(false);
            symbol->setVisible(true);
            name->setVisible(true);
            cardinality1->setVisible(true);
            cardinality2->setVisible(true);
            symbol->setBrush(QBrush{Qt::white});
            entityModel->SetRelationType(Enums::asociation);
            break;
        case 1:
            arrow1->setVisible(false);
            arrow2->setVisible(false);
            symbol->setVisible(true);
            name->setVisible(true);
            cardinality1->setVisible(true);
            cardinality2->setVisible(true);
            symbol->setBrush(QBrush{Qt::black});
            entityModel->SetRelationType(Enums::composition);
            break;
        case 2:
            arrow1->setVisible(false);
            arrow2->setVisible(false);
            symbol->setVisible(false);
            name->setVisible(true);
            cardinality1->setVisible(true);
            cardinality2->setVisible(true);
            entityModel->SetRelationType(Enums::agregation);
            break;
        case 3:
            arrow1->setVisible(true);
            arrow2->setVisible(true);
            name->setVisible(false);
            symbol->setVisible(false);
            cardinality1->setVisible(false);
            cardinality2->setVisible(false);
            entityModel->SetRelationType(Enums::generalisation);
            break;
    }
}

QPointF Connection::GetPosition1()
{
    return node1->pos();
}

QPointF Connection::GetPosition2()
{
    return node2->pos();
}

void Connection::UpdateText(QString value)
{
    entityModel->SetName(value.toStdString());
}

void Connection::CardinalityUpdate()
{
    entityModel->ChangeCardinality1(static_cast<Enums::Cardinalities>(cardinality1->GetState()));
    entityModel->ChangeCardinality2(static_cast<Enums::Cardinalities>(cardinality2->GetState()));
}

QGraphicsLineItem *Connection::GetMainLine()
{
    return mainLine;
}

void Connection::DeleteThis()
{
    delete this;
}

Connection::~Connection()
{
    delete cardinality1;
    delete cardinality2;
    delete symbol;
    delete position1;
    delete position2;
    delete name;
    delete arrow1;
    delete arrow2;
    delete mainLine;
}
