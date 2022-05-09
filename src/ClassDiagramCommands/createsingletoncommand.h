/**
 * @file createsingletoncommand.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Command for creating singleton connections
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CREATESINGLETONCOMMAND_H
#define CREATESINGLETONCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/DiagramEntity.h"
#include <QList>
#include "../ClsDiagItems/classdiagramitem.h"

class CreateSingletonCommand : public QUndoCommand
{
    public:
    /**
         * @brief CreateSingletonCommand
         * @param model is main model
         * @param item is class
         * @param node1 is first node
         * @param node2 is second node
         * @param singletons list of singleton connections
         * @param parent
         */
        CreateSingletonCommand(Model *model, ClassDiagramItem *item, QGraphicsEllipseItem *node1, QGraphicsEllipseItem *node2,
                               QList<SingletonConnection*> *singletons, QUndoCommand *parent = nullptr);
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
         * @brief singleton
         */
        SingletonConnection *singleton;
        /**
         * @brief model
         */
        Model *model;
        /**
         * @brief relationEntity
         */
        RelationEntity *relationEntity;
        /**
         * @brief singletons
         */
        QList<SingletonConnection*> *singletons;
        /**
         * @brief node1
         */
        QGraphicsEllipseItem *node1;
        /**
         * @brief node2
         */
        QGraphicsEllipseItem *node2;
};

#endif // CREATESINGLETONCOMMAND_H
