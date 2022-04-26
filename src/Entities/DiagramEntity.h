#ifndef __DIAGRAM_ENTITY__
#define __DIAGRAM_ENTITY__

#include <vector>
#include <string>

#include "RelationEntity.h"
#include "ModelObject.h"
#include "../Common/enums.h"
#include "Model.h"
#include "AttributeEntity.h"

class RelationEntity;
class Model;

class DiagramEntity : public ModelObject
{
private:
    const long ID;
    static long ID_generator;

    std::string name;
    std::vector<AttributeEntity *> attributes;
    std::vector<RelationEntity *> relations;

public:
    DiagramEntity();
    explicit DiagramEntity(std::string);

    void AddAttrib(Enums::Attrib_type, std::string);
    inline void UpdateAttribAt(std::size_t, std::string new_data);
    inline void SwitchAttribTypeAt(std::size_t);
    void RemoveAttribLast();
    void RemoveAttribAt(std::size_t);

    std::string GetName();
    void SetName(std::string);
    const long GetId();

    RelationEntity *CreateRelation(DiagramEntity &, Model *); // for use by user
    RelationEntity *CreateRelation(std::string, DiagramEntity &,
                                   Enums::RelationTypes, Enums::RelationSite,
                                   Enums::Cardinalities, Enums::Cardinalities, Model *); // for use from file
    bool RemoveRelationFromVector(RelationEntity *);

    bool operator==(DiagramEntity &);
    bool operator!=(DiagramEntity &);

    void ChangePosition(int pos_x, int pos_y);

    ~DiagramEntity();
};

#endif
