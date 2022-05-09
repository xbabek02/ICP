#include "classdiagramitem.h"

#define DEFAULT_WIDTH 150

//class representantion in diagram
ClassDiagramItem::ClassDiagramItem(QGraphicsScene *scene, DiagramEntity *entityModel, QObject *parent)
    : QObject(parent)
{
    this->entityModel = entityModel;
    entityModel->SetDiagramItem(this);
    width = DEFAULT_WIDTH;
    numberOfRows = 0;
    mainBody = new ClassItemHead(GetWidth(), GetHeight());
    scene->addItem(mainBody);

    TextItem *text = new TextItem(mainBody);
    text->SetId(numberOfRows);
    text->setPos(20, 5);
    text->setPlainText(QString::fromStdString(entityModel->GetName()));

    methodRowIndex = 0;

    qDebug() << methodRowIndex << "   " << entityModel->GetFirstMethodIndex();
    CreateNodes();
    LoadModel();

    qDebug() << methodRowIndex << "   " << entityModel->GetFirstMethodIndex();

    connect(text, SIGNAL(valueChanged(QString,int)), this, SLOT(NameChanged(QString)));
    connect(mainBody, SIGNAL(positionChange(QPointF)), this, SLOT(PositionChange(QPointF)));
    connect(mainBody, SIGNAL(mouseReleaseSignal(QPointF)), this, SLOT(SetLastPosition(QPointF)));

    positionHistory.append(GetMainBody()->pos());
    Check();
}

ClassItemHead *ClassDiagramItem::GetMainBody()
{
    return mainBody;
}

void ClassDiagramItem::CreateNodes()
{
    for(int i {0}; i < 3; i++)
    {
        for(int a {0}; a < 3; a++)
        {
            if(i == 1 && a == 1)
                continue;
            AddNode(QPointF(i * GetWidth()/2, a * GetHeight()/2));
        }
    }
}

DiagramEntity *ClassDiagramItem::GetModel()
{
    return this->entityModel;
}

void ClassDiagramItem::LoadModel()
{
    methodRowIndex = entityModel->GetFirstMethodIndex();
    for(std::size_t i {0}; i < entityModel->AttribCount(); i++)
    {
        QString value = QString::fromStdString(entityModel->GetAttribAt(i)->GetData());
        AddRow(value, Qt::lightGray);
        accesses[i]->SetState(static_cast<int>(entityModel->GetAttribAt(i)->GetAccess()));
    }
    SetWidth(entityModel->GetWidth());
    mainBody->SetWidth(entityModel->GetWidth());
    mainBody->setX(entityModel->GetPosX());
    mainBody->setY(entityModel->GetPosY());
}

void ClassDiagramItem::AddNode(QPointF position)
{
    QGraphicsEllipseItem *ellipse = new QGraphicsEllipseItem(mainBody);
    ellipse->setRect(-5,-5,10,10);
    QColor *color = new QColor;
    color->setRgb(232, 149, 55);
    ellipse->setBrush(QBrush{*color});
    ellipse->setPen(QPen{Qt::darkGray});
    ellipse->setPos(position);
    ellipse->setFlag(QGraphicsItem::ItemIsSelectable);
    ellipse->setZValue(500);
    nodes.append(ellipse);
}

void ClassDiagramItem::UpdateNodes()
{
    int count {0};

    for(int i {0}; i < 3; i++)
    {
        for(int a {0}; a < 3; a++)
        {
            if(i == 1 && a == 1)
                continue;
            nodes[count]->setPos(QPointF(i * GetWidth()/2, a * GetHeight()/2));
            count++;
        }
    }
}

void ClassDiagramItem::NewRow(QColor color)
{
    if(numberOfRows == methodRowIndex)
        methodRowIndex++;
    if(numberOfRows < methodRowIndex)
    {
        entityModel->AddAttrib(Enums::Attrib_type::field, "type variable");
        AddRow("type variable", color);
    }
    else
    {
        entityModel->AddAttrib(Enums::Attrib_type::field, "type method()");
        AddRow("type method()", color);
    }
}

//adds one class item -> creates new rectangle and editable text
void ClassDiagramItem::AddRow(QString textValue, QColor color)
{
    numberOfRows++;
    auto rect = new QGraphicsRectItem(0,0 + 30 * numberOfRows,GetWidth(), 30, mainBody);
    rect->setBrush(QBrush{color});
    rect->setPen(QPen{Qt::darkGray, 0});

    TextItem *text = new TextItem(mainBody);
    text->SetId(numberOfRows - 1);
    text->setPos(20, 5 + 30 * numberOfRows);
    text->setTextWidth(width - 30);
    text->setPlainText(textValue);
    text->setZValue(100);

    TextStateItem *access = new TextStateItem(mainBody, numberOfRows - 1);
    access->FillAccess();
    access->setPos(0, 5 + 30 * numberOfRows);

    qDebug() << "ee";

    connect(text, SIGNAL(valueChanged(QString,int)), this, SLOT(RowChanged(QString,int)));
    connect(access, SIGNAL(stateChange(int)), this, SLOT(AccessUpdate(int)));

    accesses.append(access);
    rows.append(rect);
    texts.append(text);
    UpdateNodes();


    mainBody->SetHeight(GetHeight());

    Check();
    entityModel->SetFirstMethodIndex(methodRowIndex);
    emit rowChangeSignal();
}

int ClassDiagramItem::GetNodeID(QGraphicsEllipseItem *node)
{
    for(int i {0}; i < nodes.count(); i++)
    {
        if(nodes[i] == node)
            return i;
    }
    return -1;
}

//removes last added rectangle
void ClassDiagramItem::RemoveRow()
{
    if(rows.empty() == true)
        return;

    numberOfRows--;

    auto deleterow = rows.last();
    auto deletetext = texts.last();
    auto deleteaccess = accesses.last();

    rows.removeLast();
    texts.removeLast();
    accesses.removeLast();

    delete deleterow;
    delete deletetext;
    delete deleteaccess;

    if(methodRowIndex >= numberOfRows)
        methodRowIndex = numberOfRows;
    UpdateNodes();
    mainBody->SetHeight(GetHeight());

    entityModel->RemoveAttribLast();
    entityModel->SetFirstMethodIndex(methodRowIndex);
    emit rowChangeSignal();
}

inline QPointF *ClassDiagramItem::GetCenter()
{
    QPointF *center = new QPointF(50 + mainBody->x(), 15 * numberOfRows  + mainBody->y());
    return center;
}

int ClassDiagramItem::GetHeight()
{
    return (numberOfRows + 1) * 30;
}

int ClassDiagramItem::GetWidth()
{
    return width;
}

void ClassDiagramItem::SetLastPosition(QPointF position)
{
    if(position == positionHistory.last())
        return;
    positionHistory.append(position);
    undoStack->push(new ClassMoveCommand(this, undoStack));
}

void ClassDiagramItem::SetUndoStack(QUndoStack *undoStack)
{
    this->undoStack = undoStack;
}

void ClassDiagramItem::LastPosition()
{
    positionHistory.removeLast();
    mainBody->setPos(positionHistory.last());
    mainBody->EmitPositionSignal();
}

void ClassDiagramItem::SetWidth(int value)
{
    width = value;
    mainBody->SetWidth(width);
    for(int i {0}; i < numberOfRows; i++)
    {
        rows[i]->setRect(0,0 + 30 * (1 + i),width, 30);
        texts[i]->setTextWidth(width - 30);
    }
    UpdateNodes();
    entityModel->SetWidth(width);
    emit rowChangeSignal();
}

QPointF *ClassDiagramItem::GetLinePoint(QPointF *destination)
{
    QPointF *point = this->GetCenter();
    QPointF *delta = new QPointF(point->x() - destination->x(), point->y() - destination->y());
    int newX = point->x();
    int newY = point->y();
    bool moved = false;

    if(std::abs(delta->y()) > 200)
    {
        if(destination->y() < point->y())
            newY = newY - 15 * numberOfRows;
        else
            newY = newY + 15 * (numberOfRows + 2);
        moved = true;
    }

    if(std::abs(delta->x()) > 100 || !moved)
    {
        if(destination->x() < point->x())
            newX = newX - 50;
        else
            newX = newX + 50;
    }

    point->setX(newX);
    point->setY(newY);
    delete delta;
    return point;
}

inline double ClassDiagramItem::PointDistance(QPointF point1, QPointF point2)
{
    QPointF delta = point1 - point2;
    return std::sqrt(delta.x() * delta.x() + delta.y() * delta.y());
}

void ClassDiagramItem::PushMethodUp()
{
    if(methodRowIndex <= 0 || numberOfRows == 0)
        return;
    methodRowIndex--;
    entityModel->GetAttribAt(methodRowIndex)->SetData("type method()");
    texts[methodRowIndex]->setPlainText("type method()");
    rows[methodRowIndex]->setBrush(Qt::gray);
    entityModel->SetFirstMethodIndex(methodRowIndex);
}

QGraphicsEllipseItem *ClassDiagramItem::GetNode(int id)
{
    return nodes[id];
}

void ClassDiagramItem::PushMethodDown()
{
    if(numberOfRows == 0)
        return;
    if(methodRowIndex >= numberOfRows)
        methodRowIndex = numberOfRows - 1;
    entityModel->GetAttribAt(methodRowIndex)->SetData("type variable");
    texts[methodRowIndex]->setPlainText("type variable");
    rows[methodRowIndex]->setBrush(Qt::lightGray);
    methodRowIndex++;
    entityModel->SetFirstMethodIndex(methodRowIndex);
}

void ClassDiagramItem::RowChanged(QString value, int id)
{
    entityModel->GetAttribAt(id)->SetData(value.toStdString());
    if(entityModel->GetAttribAt(id)->IsOK() != true || (id < methodRowIndex && entityModel->GetAttribAt(id)->IsMethod())
        || (id >= methodRowIndex && !entityModel->GetAttribAt(id)->IsMethod()))
        rows[id]->setBrush(QBrush{Qt::red});
    else if(id < methodRowIndex)
        rows[id]->setBrush(QBrush{Qt::lightGray});
    else
        rows[id]->setBrush(QBrush{Qt::gray});
}

QList<SingletonConnection*> ClassDiagramItem::GetSingletonViewItems()
{
    return entityModel->GetSingletonViewItems();
}

void ClassDiagramItem::Check()
{
    for(int i {0}; i < numberOfRows; i++)
    {
        if(entityModel->GetAttribAt(i)->IsOK() != true || (i < methodRowIndex && entityModel->GetAttribAt(i)->IsMethod())
            || (i >= methodRowIndex && !entityModel->GetAttribAt(i)->IsMethod()))
            rows[i]->setBrush(QBrush{Qt::red});
        else if(i < methodRowIndex)
            rows[i]->setBrush(QBrush{Qt::lightGray});
        else
            rows[i]->setBrush(QBrush{Qt::gray});
    }
}

void ClassDiagramItem::NameChanged(QString name)
{
    entityModel->SetName(name.toStdString());
}

void ClassDiagramItem::PositionChange(QPointF pos)
{
    entityModel->ChangePosition(pos.x(), pos.y());
}

QList<Connection*> ClassDiagramItem::GetRelationViewItems()
{
    return entityModel->GetRelationViewItems();
}

void ClassDiagramItem::AccessUpdate(int id)
{
    entityModel->GetAttribAt(id)->SetAccess(static_cast<Enums::AccessModifiers>(accesses[id]->GetState()));
}

ClassDiagramItem::~ClassDiagramItem()
{
    delete mainBody;
}
