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

public:
    explicit DiagramEntity(std::string);
    void AddAttrib(std::string);
    std::string GetName();
    void AddRelation(DiagramEntity &);                                                          // for use by user
    void AddRelation(std::string, DiagramEntity &, Enums::Cardinalities, Enums::Cardinalities); // for use from file
    ~DiagramEntity();
};

#endif
