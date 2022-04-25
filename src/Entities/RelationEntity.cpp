#include "RelationEntity.h"
#include "DiagramEntity.h"
#include "../Common/enums.h"

#include <iostream>
#include <string>

long RelationEntity::ID_generator = 0;

RelationEntity::RelationEntity(std::string name, DiagramEntity *first, DiagramEntity *second,
                               Enums::RelationTypes type, Enums::RelationSite site,
                               Enums::Cardinalities c1, Enums::Cardinalities c2)
    : relation_name(name), ID(ID_generator++), first(first), second(second),
      site(site), type(type), cardinality1(c1), cardinality2(c2)
{
    enitites = std::make_pair(first, second);
}

RelationEntity::RelationEntity(DiagramEntity *first, DiagramEntity *second)
    : relation_name("<<empty " + std::to_string(ID_generator) + ">>"),
      ID(ID_generator), first(first), second(second),
      type(Enums::RelationTypes::asociation), site(Enums::RelationSite::first),
      cardinality1(Enums::Cardinalities::one), cardinality2(Enums::Cardinalities::one)
{
    enitites = std::make_pair(first, second);
    ID_generator++;
}

inline void RelationEntity::SwitchRelationSite()
{
    site = (site == Enums::RelationSite::first) ? Enums::RelationSite::second : Enums::RelationSite::first;
}

inline void RelationEntity::AddRelationEntity(DiagramEntity *relationEntity)
{
    if (this->HasRelationEntity())
    {
        throw ReplacingRelationEntityException();
    }
    this->relation_diagramEntity = relationEntity;
}

bool inline RelationEntity::HasRelationEntity()
{
    // does it already have a relation entity?
    return (this->relation_diagramEntity != nullptr);
}

void RelationEntity::AddRelationEntity()
{
    if (this->HasRelationEntity())
    {
        throw ReplacingRelationEntityException();
    }
    try
    {
        this->relation_diagramEntity = new DiagramEntity(this->relation_name);
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "bad_alloc detected: " << e.what();
        exit(1);
    }
}

inline void RelationEntity::ChangeCardinality1(Enums::Cardinalities arg)
{
    this->cardinality1 = arg;
}

inline void RelationEntity::ChangeCardinality2(Enums::Cardinalities arg)
{
    this->cardinality2 = arg;
}

long RelationEntity::GetId()
{
    return this->ID;
}

std::string RelationEntity::GetName()
{
    return this->relation_name;
}

bool RelationEntity::SetName(std::string name)
{
    this->relation_name = name;
    return true;
}

std::pair<DiagramEntity *, DiagramEntity *> &RelationEntity::GetEntites()
{
    return this->enitites;
}
bool RelationEntity::operator==(RelationEntity &other)
{
    if (this->ID == other.ID)
    {
        return true;
    }
    return false;
}

bool RelationEntity::operator!=(RelationEntity &other)
{
    if (this->ID == other.ID)
    {
        return false;
    }
    return true;
}

RelationEntity::~RelationEntity()
{
    this->first->RemoveRelationFromVector(this);
    this->second->RemoveRelationFromVector(this);
    // remove relation entity??
    if (HasRelationEntity())
    {
        delete this->relation_diagramEntity;
    }
}
