#ifndef __MODEL_H__
#define __MODEL_H__

#include "DiagramEntity.h"
#include "RelationEntity.h"
#include "ModelObject.h"

#include <vector>

class RelationEntity;
class DiagramEntity;

class Model
{
private:
    static int default_pos_x;
    static int default_pos_y;
    static const int max_pos_x = INT32_MAX; // need to be updated
    static const int max_pos_y = INT32_MAX;

    std::vector<DiagramEntity *> entities;
    std::vector<RelationEntity *> relations;

public:
    DiagramEntity *CreateEntity();
    DiagramEntity *CreateEntity(std::string);
    DiagramEntity *CreateEntity(std::string, int pos_x, int pos_y);
    DiagramEntity *GetEntityById(long Id);

    RelationEntity *CreateRelation(DiagramEntity &, DiagramEntity &); // for use by user
    RelationEntity *CreateRelation(std::string, DiagramEntity &, DiagramEntity &,
                                   Enums::Cardinalities, Enums::Cardinalities); // for use from file

    void DeleteEntity(DiagramEntity *);
    bool DeleteEntityById(long Id);

    void DeleteRelation(RelationEntity *);
    bool DeleteRelationById(long Id);

    RelationEntity *GetRelationById(long Id);

    void PushRelation(RelationEntity *);

    Model();
    ~Model();

    // exceptions
    class NameExistsException
    {
    };
    class AllocException
    {
    };
};

#endif