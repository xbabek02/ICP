#ifndef CLASSMOVECOMMAND_H
#define CLASSMOVECOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/DiagramEntity.h"
#include <QList>
#include "../ClsDiagItems/classdiagramitem.h"
#include <QUndoStack>
#include <QGraphicsObject>
#include <QObject>

class ClassDiagramItem;

class ClassMoveCommand :public QUndoCommand
{

public:
    explicit ClassMoveCommand(ClassDiagramItem *item, QUndoStack *undoStack, QUndoCommand *parent = nullptr);
    ~ClassMoveCommand();
    void undo() override;
    void redo() override;

private:
    ClassDiagramItem *item;
    QUndoStack *undoStack;
};

#endif // CLASSMOVECOMMAND_H
