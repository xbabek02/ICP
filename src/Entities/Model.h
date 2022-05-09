/**
 * @file Model.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Unified storage model for all the data of class diagram
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __MODEL_H__
#define __MODEL_H__

#include "DiagramEntity.h"
#include "RelationEntity.h"
#include "ModelObject.h"
#include <QGraphicsScene>
#include <QUndoStack>
#include <QObject>

#include <vector>

class RelationEntity;
class DiagramEntity;
class AttributeEntity;

/**
 * @brief The Model class
 * Implements data storage model for the application
 * Relations and Entities can be created within given model through implemented methods
 */
class Model
{
private:
    static int default_pos_x;
    static int default_pos_y;
    static const int max_pos_x = INT32_MAX; // need to be updated
    static const int max_pos_y = INT32_MAX;

    std::vector<DiagramEntity *> entities;
    std::vector<RelationEntity *> relations;

    QGraphicsScene *scene;
    QUndoStack *undoStack;

public:
    /**
     * @brief Creates a DiagramEntity object with default values
     *
     * @return DiagramEntity* or null if failed
     */
    DiagramEntity *CreateEntity();

    /**
     * @brief Create a Entity object with already known name
     *
     * @param name
     * @return DiagramEntity* or null if failed
     */
    DiagramEntity *CreateEntity(std::string name);

    /**
     * @brief Create a Entity object with known initial parameters
     *
     * @param name
     * @param pos_x
     * @param pos_y
     * @return DiagramEntity*
     */
    DiagramEntity *CreateEntity(std::string name, int pos_x, int pos_y);

    /**
     * @brief Get the Entity from model By Id
     *
     * @param Id
     * @return DiagramEntity*
     */
    DiagramEntity *GetEntityById(long Id);

    /**
     * @brief Get the vector reference of all entities
     *
     * @return std::vector<DiagramEntity *>&
     */
    std::vector<DiagramEntity *> &GetEntities();

    /**
     * @brief Get the vector reference of all relations
     *
     * @return std::vector<RelationEntity *>
     */
    std::vector<RelationEntity *> GetRelations();

    /**
     * @brief Create a relation in model with default parameters
     *
     * @param e1 first entity
     * @param e2 second entity
     * @return RelationEntity*
     */
    RelationEntity *CreateRelation(DiagramEntity &e1, DiagramEntity &e2); // for use by user

    /**
     * @brief Create a Relation object with all knew parameters
     *
     * @param name of relation (display value)
     * @param e1 first entity
     * @param e2 second entity
     * @param type of relation
     * @param side where type of relation comes in place
     * @param c1 cardinality of relation at first entities side
     * @param c2 cardinality of relation at second entities side
     * @param node1 joint of first entity (int 0-7)
     * @param node2 joint of second entity (int 0-7)
     * @param distance distance of single entity relations from entity
     * @return RelationEntity*
     */
    RelationEntity *CreateRelation(std::string name, DiagramEntity &e1, DiagramEntity &e2,
                                   Enums::RelationTypes type, Enums::RelationSide side,
                                   Enums::Cardinalities c1, Enums::Cardinalities c2,
                                   int node1, int node2, int distance); // for use from file
    /**
     * @brief Create a Relation object with all knew parameters
     *
     * @param name of relation (display value)
     * @param id1 first entity
     * @param id2 second entity
     * @param type of relation
     * @param side where type of relation comes in place
     * @param c1 cardinality of relation at first entities side
     * @param c2 cardinality of relation at second entities side
     * @param node1 joint of first entity (int 0-7)
     * @param node2 joint of second entity (int 0-7)
     * @param distance distance of single entity relations from entity
     * @return RelationEntity*
     */
    RelationEntity *CreateRelationById(std::string name, long id1, long id2,
                                       Enums::RelationTypes type, Enums::RelationSide side,
                                       Enums::Cardinalities c1, Enums::Cardinalities c2,
                                       int node1, int node2, int distance); // for use from file

    /**
     * @brief Deletes entity at given pointer
     *
     */
    void DeleteEntity(DiagramEntity *);

    /**
     * @brief Deletes entity from model by given ID
     *
     * @param Id
     * @return true if succeeds
     * @return false if fails
     */
    bool DeleteEntityById(long Id);

    /**
     * @brief Set the Scene to the model
     *
     * @param scene
     */
    void SetScene(QGraphicsScene *scene);

    /**
     * @brief Get the Scene object
     *
     * @return QGraphicsScene*
     */
    QGraphicsScene *GetScene();

    /**
     * @brief Set the Undo Stack object
     *
     * @param undoStack
     */
    void SetUndoStack(QUndoStack *undoStack);

    /**
     * @brief Get the Undo Stack object
     *
     * @return QUndoStack*
     */
    QUndoStack *GetUndoStack();

    /**
     * @brief Deletes relation from given pointer
     *
     * @param relation
     */
    void DeleteRelation(RelationEntity *relation);

    /**
     * @brief Delete the relation of specified id
     *
     * @param Id
     * @return true if exists
     * @return false if doesn't
     */
    bool DeleteRelationById(long Id);

    /**
     * @brief Get the Relation By Id
     *
     * @param Id
     * @return RelationEntity*
     */
    RelationEntity *GetRelationById(long Id);

    /**
     * @brief Pushes the relation to the model memory
     *
     */
    void PushRelation(RelationEntity *);

    /**
     * @brief Get the Attribute Entity By Name (display value)
     *
     * @param de Diagram entity
     * @param name of attribute
     * @return AttributeEntity*
     */
    AttributeEntity *GetAttributeEntityByName(DiagramEntity *de, std::string name);

    /**
     * @brief Saves the model state in XML representation to the file at specified path
     *
     * @param path
     */
    void SaveToFile(const char *path);

    /**
     * @brief Loads the model data from the file
     *
     * @param path of the file
     * @return true if succeeded
     * @return false if file does not exist
     */
    bool LoadFromFile(const char *path);

    Model();
    virtual ~Model();

    // exceptions
    class AllocException
    {
    };
};

#endif
