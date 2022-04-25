#ifndef __DIAGRAM_ENTITY__
#define __DIAGRAM_ENTITY__

#include <vector>
#include <string>

#include "RelationEntity.h"
#include "ModelObject.h"
#include "../Common/enums.h"
#include "Model.h"

class RelationEntity;
class Model;

class DiagramEntity : public ModelObject
{
private:
    std::string name;
    std::vector<std::string> attributes;
    std::vector<RelationEntity *> relations;
    const long ID;
    static long ID_generator;

public:
    DiagramEntity();
    explicit DiagramEntity(std::string);
    void AddAttrib(std::string);
    void RemoveAttrib(std::string);
    std::string GetName();
    void SetName(std::string);
    const long GetId();
    RelationEntity *CreateRelation(DiagramEntity &, Model *);                                                          // for use by user
    RelationEntity *CreateRelation(std::string, DiagramEntity &, Enums::Cardinalities, Enums::Cardinalities, Model *); // for use from file
    bool operator==(DiagramEntity &);
    bool operator!=(DiagramEntity &);
    void ChangePosition(int pos_x, int pos_y);

    bool RemoveRelationFromVector(RelationEntity *);

    ~DiagramEntity();
};

#endif
