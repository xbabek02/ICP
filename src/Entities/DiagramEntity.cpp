#include <vector>
#include <string>
#include <new>
#include <iostream>

#include "RelationEntity.h"
#include "DiagramEntity.h"
#include "../Common/enums.h"

DiagramEntity::DiagramEntity(std::string name) : name(name)
{
}

DiagramEntity::~DiagramEntity()
{
    for (auto relation : this->relations)
    {
        delete relation;
    }
}

void DiagramEntity::AddAttrib(std::string attrib)
{
    this->attributes.push_back(attrib);
}

void DiagramEntity::AddRelation(DiagramEntity &entity)
{
    RelationEntity *relation;
    try
    {
        relation = new RelationEntity(this, &entity);
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "bad_alloc detected: " << e.what();
        exit(1);
    }
    this->relations.push_back(relation);
}

void DiagramEntity::AddRelation(std::string name, DiagramEntity &entity, Enums::Cardinalities cardinality1, Enums::Cardinalities cardinality2)
{
    RelationEntity *relation;
    try
    {
        relation = new RelationEntity(name, this, &entity, cardinality1, cardinality2);
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "bad_alloc detected: " << e.what();
        exit(1);
    }
    this->relations.push_back(relation);
}

std::string DiagramEntity::GetName()
{
    return this->name;
}