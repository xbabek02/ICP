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


/**
 * @brief The DiagramEntity class
 * Represents stored data of relation entities
 * Data stored are used for both class diagram and sequence diagram entities
 */
class DiagramEntity : public ModelObject
{
private:
    const int ID;
    static int ID_generator;

    std::string name;
    std::vector<AttributeEntity *> attributes;
    std::vector<RelationEntity *> relations;

public:
    DiagramEntity();
    explicit DiagramEntity(std::string);

    void AddAttrib(Enums::Attrib_type, std::string);
    AttributeEntity*GetAttribAt(std::size_t index);
    std::size_t AttribCount();
    inline void UpdateAttribAt(std::size_t, std::string new_data);
    inline void SwitchAttribTypeAt(std::size_t);
    void RemoveAttribLast();
    void RemoveAttribAt(std::size_t);

    std::string GetName();
    void SetName(std::string);
    int GetId();

    RelationEntity *CreateRelation(DiagramEntity &, Model *); // for use by user
    RelationEntity *CreateRelation(std::string, DiagramEntity &,
                                   Enums::RelationTypes, Enums::RelationSide,
                                   Enums::Cardinalities, Enums::Cardinalities, Model *,
                                   int node1, int node2, int distance); // for use from file
    bool RemoveRelationFromVector(RelationEntity *);

    bool operator==(DiagramEntity &);
    bool operator!=(DiagramEntity &);

    void ChangePosition(int pos_x, int pos_y);

    ~DiagramEntity();
};

#endif
