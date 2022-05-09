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
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @return The test results
     */
    void NewRow(QColor color);

    /**
     * a normal member taking two arguments and returning an integer value.
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @see Javadoc_Test()
     * @see ~Javadoc_Test()
     * @see testMeToo()
     * @see publicVar()
     * @return The test results
     */
    void AddRow(QString textValue, QColor color);

    /**
     * a normal member taking two arguments and returning an integer value.
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @return The test results
     */
    TextItem *text;

    /**
     * a normal member taking two arguments and returning an integer value.
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @return The test results
     */
    void RemoveRow();

    /**
     * a normal member taking two arguments and returning an integer value.
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @return The test results
     */
    void PushMethodUp();

    /**
     * a normal member taking two arguments and returning an integer value.
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @return The test results
     */
    void PushMethodDown();

    /**
     * a normal member taking two arguments and returning an integer value.
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @return The test results
     */
    void SetUndoStack(QUndoStack *undoStack);

    /**
     * a normal member taking two arguments and returning an integer value.
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @return The test results
     */
    int GetNodeID(QGraphicsEllipseItem *node);

    /**
     * a normal member taking two arguments and returning an integer value.
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @return The test results
     */
    void ModelNameChanged(QString name);

    /**
     * a normal member taking two arguments and returning an integer value.
     * @param a an integer argument.
     * @param s a constant character pointer.
     * @return The test results
     */
    int GetHeight();
    int GetWidth();
    void LastPosition();
    void SetWidth(int value);
    ClassItemHead *GetMainBody();
    DiagramEntity *GetModel();
    QPointF *GetCenter();
    QPointF *GetLinePoint(QPointF *destination);
    QGraphicsEllipseItem *GetNode(int id);
    QList<Connection*> GetRelationViewItems();


signals:
    void PositionSignal(QPointF position);
    void rowChangeSignal();
    void moveUndoSignal(ClassDiagramItem *thisObject);

public slots:
    void RowChanged(QString value, int id);
    void PositionChange(QPointF pos);
    void NameChanged(QString value);
    void AccessUpdate(int id);
    void SetLastPosition(QPointF position);

private:
    void AddNode(QPointF position);
    void UpdateNodes();
    void CreateNodes();
    void LoadModel();
    void Check();
    double PointDistance(QPointF point1, QPointF point2);
    QList<QPointF> positionHistory;
    QList<QGraphicsRectItem*> rows;
    QList<QGraphicsTextItem*> texts;
    QList<TextStateItem*> accesses;
    QList<QGraphicsEllipseItem*> nodes;
    DiagramEntity *entityModel;
    QString classNameText;
    ClassItemHead *mainBody;
    QUndoStack *undoStack;
    int numberOfRows;
    int methodRowIndex;
    int width;
};

#endif // CLASSDIAGRAMITEM_H
