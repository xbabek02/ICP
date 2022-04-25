#ifndef __DIAGRAM_ENTITY__
#define __DIAGRAM_ENTITY__

#include <vector>
#include <string>

#include "RelationEntity.h"
#include "../Common/enums.h"

class RelationEntity;

class DiagramEntity
{
private:
    std::string name;
    std::vector<std::string> attributes;
    std::vector<RelationEntity *> relations;
    const long ID;
    static long ID_generator;

public:
    explicit DiagramEntity(std::string);
    void AddAttrib(std::string);
    std::string GetName();
    RelationEntity *AddRelation(DiagramEntity &);                                                          // for use by user
    RelationEntity *AddRelation(std::string, DiagramEntity &, Enums::Cardinalities, Enums::Cardinalities); // for use from file
    RelationEntity *GetRelation(DiagramEntity &, std::string);
    bool operator==(DiagramEntity &);
    bool operator!=(DiagramEntity &);
    ~DiagramEntity();
};

#endif
