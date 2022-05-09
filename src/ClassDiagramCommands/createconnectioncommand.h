/**
 * @file createconnectioncommand.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Command for creating connection
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CREATECONNECTIONCOMMAND_H
#define CREATECONNECTIONCOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/RelationEntity.h"
#include <QList>
#include "../ClsDiagItems/connection.h"

class CreateConnectionCommand : public QUndoCommand
{
    public:
    /**
         * @brief CreateConnectionCommand
         * @param model is main model
         * @param item1 is first class
         * @param item2 is second class
         * @param node1 is first classes node
         * @param node2 is second node
         * @param connections is list of connections
         * @param scene is graphics scene
         * @param entity is model entity
         * @param parent
         */
        CreateConnectionCommand(Model *model, ClassDiagramItem *item1, ClassDiagramItem *item2, QGraphicsEllipseItem *node1, QGraphicsEllipseItem *node2,
                                QList<Connection*> *connections, QGraphicsScene *scene, RelationEntity *entity = nullptr, QUndoCommand *parent = nullptr);
        CreateConnectionCommand(QGraphicsScene *scene, RelationEntity *relation);

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
         * @brief connection
         */
        Connection *connection;

        /**
         * @brief scene
         */
        QGraphicsScene *scene;

        /**
         * @brief model
         */
        Model *model;

        /**
         * @brief connections
         */

        QList<Connection*> *connections;
        /**
         * @brief relationModel
         */
        RelationEntity *relationModel;

        /**
         * @brief item1
         */
        ClassDiagramItem *item1 = nullptr;

        /**
         * @brief item2
         */
        ClassDiagramItem *item2;

        /**
         * @brief node1
         */
        QGraphicsEllipseItem *node1;

        /**
         * @brief node2
         */
        QGraphicsEllipseItem *node2;
};

#endif // CREATECONNECTIONCOMMAND_H
