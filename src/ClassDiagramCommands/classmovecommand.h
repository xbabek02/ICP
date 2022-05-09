/**
 * @file classmovecommand.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Commend for moving class in class diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

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
    /**
     * @brief ClassMoveCommand is constructor
     * @param item is moved item
     * @param undoStack
     * @param parent
     */
    explicit ClassMoveCommand(ClassDiagramItem *item, QUndoStack *undoStack, QUndoCommand *parent = nullptr);
    ~ClassMoveCommand();

    /**
     * @brief undo
     */
    void undo() override;

    /**
     * @brief redo
     */
    void redo() override;

private:
    /**
     * @brief item
     */
    ClassDiagramItem *item;

    /**
     * @brief undoStack
     */
    QUndoStack *undoStack;
};

#endif // CLASSMOVECOMMAND_H
