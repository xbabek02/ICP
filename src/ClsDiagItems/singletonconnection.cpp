#include "singletonconnection.h"
#include <QVector2D>

#define NUMBER_OF_STATES 4
#define LINE_Z_VALUE -500
#define LINE_THICKNESS 3
#define IMPLICIT_DISTANCE 80

SingletonConnection::SingletonConnection(ClassDiagramItem *item, QGraphicsEllipseItem *node1,
                                         QGraphicsEllipseItem *node2, RelationEntity *entityModel, QObject *parent) : QObject(parent)
{
    distance = IMPLICIT_DISTANCE;
    entityModel->ChangeNode1(item->GetNodeID(node1));
    entityModel->ChangeNode2(item->GetNodeID(node2));
    entityModel->ChangeDistance(distance);
    entityModel->SetSingletonViewItem(this);
    this->entityModel = entityModel;
    this->item = item;
    this->node1 = node1;
    this->node2 = node2;
    Draw();
    DrawSymbol(false);
    DrawArrow(false);
    DrawText(false);
    PutCardinalities(false);
    cardinality1->SetState(entityModel->GetCardinalities().first);
    cardinality2->SetState(entityModel->GetCardinalities().second);
    currentState = static_cast<int>(entityModel->GetType());
    numberOfStates = NUMBER_OF_STATES;
    currentState--;
    ChangeState();
    connect(item, SIGNAL(rowChangeSignal()), this, SLOT(Update()));
    connect(cardinality1, SIGNAL(stateChange(int)), this, SLOT(ModelUpdate()));
    connect(cardinality2, SIGNAL(stateChange(int)), this, SLOT(ModelUpdate()));
    connect(text, SIGNAL(valueChanged(QString, int)), this, SLOT(ModelUpdate()));
}

void SingletonConnection::Delete()
{
    for(auto line : lines)
        delete line;
    lines.clear();
}

void SingletonConnection::DrawSymbol(bool update)
{
    if(update == false)
    {
        symbol = new QGraphicsEllipseItem(item->GetMainBody());
        symbol->setPen(QPen{Qt::black, 3});
        symbol->setVisible(false);
    }
    QPointF position = GetLineMidPoint(lines[0], 2);
    symbol->setRect(position.x() - 10, position.y() - 10, 20, 20);
}

int SingletonConnection::GetDistance()
{
    return distance;
}

void SingletonConnection::SetDistance(int value)
{
    distance = value;
    entityModel->ChangeDistance(distance);
    Update();
}

void SingletonConnection::PutCardinalities(bool update)
{
    if(update == false)
    {
        cardinality1 = new TextStateItem(item->GetMainBody());
        cardinality2 = new TextStateItem(item->GetMainBody());
        cardinality1->FillCardinalities();
        cardinality2->FillCardinalities();
    }
    cardinality1->setPos(GetLineMidPoint(lines[0], 2) + QPointF(0,10));
    cardinality2->setPos(GetLineMidPoint(lines[1], 2) + QPointF(0,10));
}

QPointF SingletonConnection::GetLineMidPoint(QGraphicsLineItem *line, double divide)
{
    QLineF linef = line->line();
    return QPointF((linef.x1() + linef.x2())/divide, (linef.y1() + linef.y2())/divide);
}

void SingletonConnection::Draw()
{
    if(node1->y() == node2->y() && node1->y() != 0 && node1->y() != item->GetHeight())
    {
        lines = NarrowLine();
    }
    else if(node1->x() == node2->x() && node1->x() != 0 && node1->x() != item->GetHeight())
    {
        lines = NarrowLine();
    }
    else if(node1->x() == node2->x())
    {
        lines = VerticalLine();
    }
    else if(node1->y() == node2->y())
    {
        lines = HorizontalLine();
    }
    else
    {
        lines = Slant();
    }

    for(auto line : lines)
    {
        line->setFlag(QGraphicsItem::ItemIsSelectable);
        connect(line, SIGNAL(selectChange(bool)), this, SLOT(Select(bool)));
    }
}

void SingletonConnection::DrawText(bool update)
{
    if(update == false)
    {
        text = new TextItem(item->GetMainBody());
        text->setPlainText(QString::fromStdString(entityModel->GetName()));
    }
    QPointF newpos = GetLineMidPoint(lines[2], 2);
    text->setPos(newpos.x(), newpos.y());
}

QList<SelectLine*> SingletonConnection::HorizontalLine()
{
    QList<SelectLine*> lines;
    QPointF point = QPointF(0,distance);
    if(node1->y() == 0)
        point = node1->pos() - point;
    else
        point = node1->pos() + point;
    SelectLine *line = new SelectLine(node1->x(),node1->y(),point.x(),point.y(), item->GetMainBody());
    lines.append(line);

    SelectLine *line2 = new SelectLine(point.x(),point.y(), node2->x(), point.y(), item->GetMainBody());
    lines.append(line2);

    SelectLine *line3 = new SelectLine(node2->x(), point.y(), node2->x(), node2->y(), item->GetMainBody());
    lines.append(line3);

    return lines;
}

QList<SelectLine*> SingletonConnection::VerticalLine()
{
    QList<SelectLine*> lines;
    QPointF point = QPointF(distance,0);
    if(node1->x() == 0)
        point = node1->pos() - point;
    else
        point = node1->pos() + point;
    SelectLine *line = new SelectLine(node1->x(),node1->y(),point.x(),point.y(), item->GetMainBody());
    lines.append(line);

    SelectLine *line2 = new SelectLine(point.x(),point.y(), point.x(), node2->y(), item->GetMainBody());
    lines.append(line2);

    SelectLine *line3 = new SelectLine(point.x(), node2->y(), node2->x(), node2->y(), item->GetMainBody());
    lines.append(line3);

    return lines;
}

QList<SelectLine*> SingletonConnection::NarrowLine()
{
    QList<SelectLine*> lines;
    if(node1->y() == node2->y())
    {
        QPointF point = QPointF(distance,0);
        if(node1->x() != 0)
            ChangeNodes();
        point = node1->pos() - point;
        SelectLine *line = new SelectLine(node1->x(), node1->y(), point.x(), point.y(), item->GetMainBody());
        SelectLine *line2 = new SelectLine(node2->x(), node2->y(), point.x() + item->GetWidth() + distance * 2, point.y(), item->GetMainBody());
        SelectLine *line3 = new SelectLine(point.x(), point.y(), point.x(),-distance, item->GetMainBody());
        SelectLine *line4 = new SelectLine(point.x() + item->GetWidth() + distance * 2, point.y(),point.x() + item->GetWidth() + distance * 2,
                                                         -distance, item->GetMainBody());
        SelectLine *line5 = new SelectLine(point.x() + item->GetWidth() + distance * 2, -distance,
                                                         point.x(),-distance, item->GetMainBody());

        lines.append(line);
        lines.append(line2);
        lines.append(line3);
        lines.append(line4);
        lines.append(line5);
    }
    else
    {
        QPointF point = QPointF(0,distance);
        if(node1->y() != 0)
            ChangeNodes();
        point = node1->pos() - point;
        SelectLine *line = new SelectLine(node1->x(), node1->y(), point.x(), point.y(), item->GetMainBody());
        SelectLine *line2 = new SelectLine(node2->x(), node2->y(), point.x(), -point.y() + item->GetHeight(), item->GetMainBody());
        SelectLine *line3 = new SelectLine(point.x(), point.y(), point.x() + item->GetWidth()/2 + distance, point.y(), item->GetMainBody());
        SelectLine *line4 = new SelectLine(point.x(), -point.y() + item->GetHeight(),point.x() + item->GetWidth()/2 + distance,
                                                          -point.y() + item->GetHeight(), item->GetMainBody());

        SelectLine *line5 = new SelectLine(point.x() + item->GetWidth()/2 + distance, point.y(),
                                                         point.x() + item->GetWidth()/2 + distance, -point.y() + item->GetHeight(), item->GetMainBody());

        lines.append(line);
        lines.append(line2);
        lines.append(line3);
        lines.append(line4);
        lines.append(line5);
    }
    return lines;
}

QList<SelectLine*> SingletonConnection::Slant()
{
    if(node1->y() < node2->y())
        ChangeNodes();
    QPointF point1;
    QPointF point2;
    QPointF commonPoint;
    if(node1->y() == item->GetHeight())
    {
        if(node1->x() == item->GetWidth()/2)
        {
            point1 = QPointF(0, distance);
            if(node2->x() < node1->x())
            {
                point2 = QPointF(-distance, 0);
                commonPoint = QPointF(-distance, item->GetHeight() + distance);
            }
            else
            {
                point2 = QPointF(distance, 0);
                commonPoint = QPointF(item->GetWidth() + distance, item->GetHeight() + distance);
            }
        }
        else if(node1->x() == 0)
        {
            if(node2->y() == item->GetHeight()/2)
            {
                point1 = QPointF(0, distance);
                point2 = QPointF(distance, 0);
                commonPoint = QPointF(item->GetWidth() + distance, item->GetHeight() + distance);
            }
            else
            {
                point1 = QPointF(-distance, 0);
                point2 = QPointF(0, -distance);
                commonPoint = QPointF(-distance, -distance);
            }
        }
        else if(node1->x() == item->GetWidth())
        {
            if(node2->y() == item->GetHeight()/2)
            {
                point1 = QPointF(0, distance);
                point2 = QPointF(-distance, 0);
                commonPoint = QPointF(-distance, item->GetHeight() + distance);
            }
            else
            {
                point1 = QPointF(distance, 0);
                point2 = QPointF(0, -distance);
                commonPoint = QPointF(item->GetWidth() + distance, -distance);
            }
        }
    }
    else if(node1->x() == 0)
    {
        point1 = QPointF(-distance, 0);
        point2 = QPointF(0, -distance);
        commonPoint = QPointF(-distance, -distance);
    }
    else
    {
        point1 = QPointF(distance, 0);
        point2 = QPointF(0, -distance);
        commonPoint = QPointF(item->GetWidth() + distance, -distance);
    }

    point1 = node1->pos() + point1;
    point2 = node2->pos() + point2;

    SelectLine *line = new SelectLine(node1->x(), node1->y(), point1.x(), point1.y(), item->GetMainBody());
    SelectLine *line2 = new SelectLine(node2->x(), node2->y(), point2.x(), point2.y(), item->GetMainBody());
    SelectLine *line3 = new SelectLine(point1.x(), point1.y(),commonPoint.x(),commonPoint.y(), item->GetMainBody());
    SelectLine *line4 = new SelectLine(point2.x(), point2.y(),commonPoint.x(),commonPoint.y(), item->GetMainBody());

    lines.append(line);
    lines.append(line2);
    lines.append(line3);
    lines.append(line4);

    return lines;
}

void SingletonConnection::ChangeNodes()
{
    QGraphicsEllipseItem *tmp = node1;
    node1 = node2;
    node2 = tmp;
}

void SingletonConnection::Select(bool selected)
{
    qDebug() << lines.count() << "hovna";
    for(auto line : lines)
    {
        line->SetSelectChain();
        line->setSelected(selected);
    }
}

void SingletonConnection::Update()
{
    Delete();
    Draw();
    DrawSymbol(true);
    DrawArrow(true);
    PutCardinalities(true);
    DrawText(true);
}

void SingletonConnection::DrawArrow(bool update)
{
    QLineF line = lines[0]->line();
    int deltaX = line.x1() - line.x2();
    int deltaY = line.y1() - line.y2();

    QVector2D vector = QVector2D(deltaX, deltaY);
    vector.normalize();
    vector = vector * 20;

    if(update == false)
    {
        arrow1 = new QGraphicsLineItem(item->GetMainBody());
        arrow2 = new QGraphicsLineItem(item->GetMainBody());
        arrow1->setPen(QPen{Qt::black,3});
        arrow2->setPen(QPen{Qt::black,3});
        arrow1->setVisible(false);
        arrow1->setVisible(false);
    }
    arrow1->setLine(line.x1(), line.y1(), line.x1() - vector.y() - vector.x(), line.y1() + vector.x() - vector.y());
    arrow2->setLine(line.x1(), line.y1(), line.x1() + vector.y() - vector.x(), line.y1() - vector.x() - vector.y());
}

void SingletonConnection::ChangeState()
{
    currentState = (currentState + 1) % numberOfStates;
    switch(currentState)
    {
        case 0:
            arrow1->setVisible(false);
            arrow2->setVisible(false);
            symbol->setVisible(true);
            text->setVisible(true);
            cardinality1->setVisible(true);
            cardinality2->setVisible(true);
            symbol->setBrush(QBrush{Qt::white});
            entityModel->SetRelationType(Enums::asociation);
            break;
        case 1:
            arrow1->setVisible(false);
            arrow2->setVisible(false);
            symbol->setVisible(true);
            text->setVisible(true);
            cardinality1->setVisible(true);
            cardinality2->setVisible(true);
            symbol->setBrush(QBrush{Qt::black});
            entityModel->SetRelationType(Enums::composition);
            break;
        case 2:
            arrow1->setVisible(false);
            arrow2->setVisible(false);
            symbol->setVisible(false);
            text->setVisible(true);
            cardinality1->setVisible(true);
            cardinality2->setVisible(true);
            entityModel->SetRelationType(Enums::agregation);
            break;
        case 3:
            arrow1->setVisible(true);
            arrow2->setVisible(true);
            text->setVisible(false);
            symbol->setVisible(false);
            cardinality1->setVisible(false);
            cardinality2->setVisible(false);
            entityModel->SetRelationType(Enums::generalisation);
            break;
    }
}

void SingletonConnection::ModelUpdate()
{
    entityModel->ChangeCardinality1(static_cast<Enums::Cardinalities>(cardinality1->GetState()));
    entityModel->ChangeCardinality2(static_cast<Enums::Cardinalities>(cardinality2->GetState()));
    entityModel->SetName(text->toPlainText().toStdString());
}

void SingletonConnection::CardinalityUpdate()
{
    entityModel->ChangeCardinality1(static_cast<Enums::Cardinalities>(cardinality1->GetState()));
    entityModel->ChangeCardinality2(static_cast<Enums::Cardinalities>(cardinality2->GetState()));
}

QGraphicsLineItem *SingletonConnection::GetMainLine()
{
    return lines[0];
}

RelationEntity *SingletonConnection::GetModel()
{
    return entityModel;
}

SingletonConnection::~SingletonConnection()
{
    for(auto line : lines)
    {
        delete line;
    }
    delete cardinality1;
    delete cardinality2;
    delete text;
    delete symbol;
    delete arrow1;
    delete arrow2;
}
