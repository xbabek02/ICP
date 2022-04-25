#include "RelationEntity.h"
#include "DiagramEntity.h"
#include "../Common/enums.h"

#include <iostream>

long RelationEntity::ID_generator = 0;

RelationEntity::RelationEntity(std::string name, DiagramEntity *first, DiagramEntity *second,
                               Enums::Cardinalities cardinality1, Enums::Cardinalities cardinality2)
    : relation_name(name), ID(ID_generator++), first(first), second(second),
      cardinality1(cardinality1), cardinality2(cardinality2)
{
    enitites = std::make_pair(first, second);
}

RelationEntity::RelationEntity(DiagramEntity *first, DiagramEntity *second)
    : relation_name("<<empty>>"), ID(ID_generator++), first(first), second(second),
      cardinality1(Enums::Cardinalities::one), cardinality2(Enums::Cardinalities::one)
{
    enitites = std::make_pair(first, second);
}

void RelationEntity::AddRelationEntity(DiagramEntity *relation)
{
    this->relation_name = relation->GetName();
    this->relation_diagramEntity = relation;
}

void RelationEntity::AddRelationEntity()
{
    if (this->relation_diagramEntity != nullptr)
    {
        // error window?
        return;
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

void RelationEntity::ChangeCardinality1(Enums::Cardinalities arg)
{
    this->cardinality1 = arg;
}

void RelationEntity::ChangeCardinality2(Enums::Cardinalities arg)
{
    this->cardinality2 = arg;
}

std::string RelationEntity::GetName()
{
    return this->relation_name;
}

std::pair<DiagramEntity *, DiagramEntity *> &RelationEntity::GetEntites()
{
    return this->enitites;
}

RelationEntity::~RelationEntity()
{
}