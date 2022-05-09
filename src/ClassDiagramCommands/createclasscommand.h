/**
 * @file createclasscommand.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Command for creating class in class diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CREATECLASSCOMMAND_H
#define CREATECLASSCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/DiagramEntity.h"
#include <QList>
#include "../ClsDiagItems/classdiagramitem.h"

class CreateClassCommand : public QUndoCommand
{
public:

    /**
     * @brief CreateClassCommand
     * @param mainModel main class diagram model
     * @param items is list of created class items
     * @param scene is graphics scene
     * @param entity is model entity
     * @param parent
     */
    CreateClassCommand(Model *mainModel, QList<ClassDiagramItem*> *items, QGraphicsScene *scene, DiagramEntity *entity = nullptr, QUndoCommand *parent = nullptr);

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
     * @brief createdItem
     */
    DiagramEntity *createdItem = nullptr;

    /**
     * @brief scene
     */
    QGraphicsScene *scene;

    /**
     * @brief mainModel
     */
    Model *mainModel;

    /**
     * @brief items
     */
    QList<ClassDiagramItem*> *items;

    /**
     * @brief lastPosition
     */
    QPointF lastPosition;
};

#endif // CREATECLASSCOMMAND_H
