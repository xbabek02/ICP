#include <vector>
#include <string>
#include <new>
#include <iostream>
#include <bits/stdc++.h>

#include "RelationEntity.h"
#include "DiagramEntity.h"
#include "../Common/enums.h"

long DiagramEntity::ID_generator = 0;

DiagramEntity::DiagramEntity(std::string name) : name(name), ID(ID_generator++)
{
}

DiagramEntity::~DiagramEntity()
{
    RelationEntity *a_temp;
    bool result;
    for (auto relation : this->relations)
    {
        auto res = relation->GetEntites();
        if (*res.first == *res.second)
            delete relation;
        else
        {
            DiagramEntity *second = ((*this == *res.first) ? res.second : res.first);
            auto it = std::remove_if(second->relations.begin(), second->relations.end(),
                                     [relation](auto a)
                                     { return a == relation; });
            second->relations.erase(it, second->relations.end());
            delete relation;
        }
    }
}

void DiagramEntity::AddAttrib(std::string attrib)
{
    this->attributes.push_back(attrib);
}

RelationEntity *DiagramEntity::GetRelation(DiagramEntity &entity, std::string name)
{
    for (auto relation : this->relations)
    {
        std::pair<DiagramEntity *, DiagramEntity *> res = relation->GetEntites();
        if ((*res.first == entity && *res.second == *this) || (*res.first == *this && *res.second == entity))
        {
            if (relation->GetName() == name)
                return relation;
        }
    }
    return nullptr;
}

RelationEntity *DiagramEntity::AddRelation(DiagramEntity &entity)
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
    if (entity != *this)
    {
        entity.relations.push_back(relation);
    }
    return relation;
}

RelationEntity *DiagramEntity::AddRelation(std::string name, DiagramEntity &entity, Enums::Cardinalities cardinality1, Enums::Cardinalities cardinality2)
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
    if (entity != *this)
    {
        entity.relations.push_back(relation);
    }
    return relation;
}

std::string DiagramEntity::GetName()
{
    return this->name;
}

bool DiagramEntity::operator==(DiagramEntity &other)
{
    if (this->ID == other.ID)
    {
        return true;
    }
    return false;
}

bool DiagramEntity::operator!=(DiagramEntity &other)
{
    if (this->ID == other.ID)
    {
        return false;
    }
    return true;
}