#ifndef __RELATION_ENTITY__
#define __RELATION_ENTITY__

#include <string>
#include "DiagramEntity.h"
#include "../Common/enums.h"

class DiagramEntity;

class RelationEntity
{
private:
    long ID;
    static long ID_generator;
    std::string relation_name;
    DiagramEntity *first, *second, *relation_diagramEntity;
    std::pair<DiagramEntity *, DiagramEntity *> enitites;
    Enums::Cardinalities cardinality1, cardinality2;

public:
    RelationEntity(std::string, DiagramEntity *, DiagramEntity *, Enums::Cardinalities, Enums::Cardinalities); // for creating from file
    RelationEntity(DiagramEntity *, DiagramEntity *);                                                          // for creating by user
    void AddRelationEntity(DiagramEntity *);
    void AddRelationEntity();
    std::string GetName();
    std::pair<DiagramEntity *, DiagramEntity *> &GetEntites();
    void ChangeCardinality1(Enums::Cardinalities);
    void ChangeCardinality2(Enums::Cardinalities);
    ~RelationEntity();
};

#endif