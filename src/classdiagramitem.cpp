#include "classdiagramitem.h"
#include <string>
#include <QDebug>

//class representantion in diagram
ClassDiagramItem::ClassDiagramItem(QGraphicsScene *scene, QObject *parent1)
    : QObject(parent1)
{
    numberOfRows = 0;
    mainBody = new ClassItemHead;
    scene->addItem(mainBody);
}

//adds one class item -> creates new rectangle and editable text
void ClassDiagramItem::AddRow()
{
    numberOfRows++;
    auto rect = new QGraphicsRectItem(0,0 + 30 * numberOfRows,100, 30, mainBody);
    auto text = new QGraphicsTextItem(mainBody);
    text->setTextInteractionFlags(Qt::TextEditorInteraction);
    text->setPos(10, 5 + 30 * numberOfRows);
    text->setPlainText("drz picu");

    rows.append(rect);
    texts.append(text);
}

//removes last added rectangle
void ClassDiagramItem::RemoveRow()
{
    if(rows.empty() == true)
        return;
    auto deleterow = rows.last();
    auto deletetext = texts.last();
    rows.removeLast();
    texts.removeLast();
    delete deleterow;
    delete deletetext;
    numberOfRows--;
}
