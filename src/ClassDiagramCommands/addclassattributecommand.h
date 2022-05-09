/**
 * @file addclassattributecommand.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Command for adding attribute to the class
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef ADDCLASSATTRIBUTECOMMAND_H
#define ADDCLASSATTRIBUTECOMMAND_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include "../Entities/Model.h"
#include "../Entities/DiagramEntity.h"
#include <QList>
#include "../ClsDiagItems/classdiagramitem.h"
#include <QUndoStack>
#include <QGraphicsObject>
#include <QObject>

/**
 * @brief Class for creating new class attribute in class diagram
 * makes undo operation possible
 */
class AddClassAttributeCommand : public QUndoCommand
{
public:
    /**
     * @brief Constructor
     * @param item is class item in diagram
     * @param parent
     */
    explicit AddClassAttributeCommand(ClassDiagramItem *item, QUndoCommand *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~AddClassAttributeCommand(){}

    /**
     * @brief method to undo the operation
     */
    void undo() override;

    /**
     * @brief method to redo the operation
     */
    void redo() override;

private:
    ClassDiagramItem *item;
};

#endif // ADDCLASSATTRIBUTECOMMAND_H
