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
    DiagramEntity *CreateEntity();
    DiagramEntity *CreateEntity(std::string);
    DiagramEntity *CreateEntity(std::string, int pos_x, int pos_y);
    DiagramEntity *GetEntityById(long Id);

    std::vector<DiagramEntity*> &GetEntities();
    std::vector<RelationEntity*> GetRelations();

    RelationEntity *CreateRelation(DiagramEntity &, DiagramEntity &); // for use by user
    RelationEntity *CreateRelation(std::string, DiagramEntity &, DiagramEntity &,
                                   Enums::RelationTypes, Enums::RelationSide,
                                   Enums::Cardinalities, Enums::Cardinalities,
                                   int node1, int node2, int distance); // for use from file

    RelationEntity *CreateRelationById(std::string, long id1, long id2,
                                       Enums::RelationTypes, Enums::RelationSide,
                                       Enums::Cardinalities, Enums::Cardinalities,
                                       int node1, int node2, int distance); // for use from file

    void DeleteEntity(DiagramEntity *);
    bool DeleteEntityById(long Id);

    void SetScene(QGraphicsScene *scene);
    QGraphicsScene *GetScene();
    void SetUndoStack(QUndoStack *undoStack);
    QUndoStack *GetUndoStack();

    void DeleteRelation(RelationEntity *);
    bool DeleteRelationById(long Id);
    RelationEntity *GetRelationById(long Id);
    void PushRelation(RelationEntity *);
    AttributeEntity *GetAttributeEntityByName(DiagramEntity*de, std::string name);

    void SaveToFile(const char*);
    bool LoadFromFile(const char*);

    Model();
    virtual ~Model();

    // exceptions
    class AllocException
    {
    };
};

#endif
