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

    Enums::RelationTypes type;
    Enums::RelationSite site;

public:
    RelationEntity(std::string, DiagramEntity *, DiagramEntity *,
                   Enums::RelationTypes, Enums::RelationSite,
                   Enums::Cardinalities, Enums::Cardinalities); // for creating from file
    RelationEntity(DiagramEntity *, DiagramEntity *);           // for creating by user

    bool inline HasRelationEntity();
    void AddRelationEntity();
    inline void AddRelationEntity(DiagramEntity *);

    long GetId();
    std::string GetName();
    bool SetName(std::string);
    std::pair<DiagramEntity *, DiagramEntity *> &GetEntites();

    inline void ChangeCardinality1(Enums::Cardinalities);
    inline void ChangeCardinality2(Enums::Cardinalities);

    inline void SwitchRelationSite();

    bool operator==(RelationEntity &other);
    bool operator!=(RelationEntity &other);

    ~RelationEntity();

    class ReplacingRelationEntityException
    {
    };
};

#endif
