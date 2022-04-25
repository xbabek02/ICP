#include <vector>
#include <string>
#include <new>
#include <iostream>
#include <bits/stdc++.h>
#include <algorithm>

#include "RelationEntity.h"
#include "DiagramEntity.h"
#include "../Common/enums.h"
#include "AttributeEntity.h"

long DiagramEntity::ID_generator = 0;

DiagramEntity::DiagramEntity(std::string name) : name(name), ID(ID_generator)
{
    ID_generator++;
}

DiagramEntity::DiagramEntity() : name("Entity " + std::to_string(ID_generator)), ID(ID_generator)
{
    ID_generator++;
}

void DiagramEntity::ChangePosition(int pos_x, int pos_y)
{
    ModelObject::ChangePosition(pos_x, pos_y);
}

void DiagramEntity::AddAttrib(Enums::Attrib_type type, std::string data)
{
    AttributeEntity *attrib;
    try
    {
        attrib = new AttributeEntity(type, data);
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "bad_alloc detected: " << e.what();
        exit(1);
    }
    this->attributes.push_back(attrib);
}

void DiagramEntity::RemoveAttribLast()
{
    if (attributes.size() > 0)
    {
        auto temp = attributes.back();
        attributes.pop_back();
        delete temp;
    }
}

void DiagramEntity::RemoveAttribAt(std::size_t index)
{
    if (attributes.size() <= index)
    {
        return;
    }

    auto temp = attributes.at(index);
    attributes.erase(attributes.begin() + index);
}

RelationEntity *DiagramEntity::CreateRelation(DiagramEntity &entity, Model *m)
{
    RelationEntity *relation;
    try
    {
        relation = new RelationEntity(this, &entity);
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "bad_alloc detected: " << e.what();
        return nullptr;
    }
    this->relations.push_back(relation);
    if (entity != *this)
    {
        entity.relations.push_back(relation);
    }
    m->PushRelation(relation);
    return relation;
}

RelationEntity *DiagramEntity::CreateRelation(std::string name, DiagramEntity &entity,
                                              Enums::RelationTypes type, Enums::RelationSite site,
                                              Enums::Cardinalities cardinality1, Enums::Cardinalities cardinality2, Model *m)
{
    RelationEntity *relation;
    try
    {
        relation = new RelationEntity(name, this, &entity, type, site, cardinality1, cardinality2);
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

    m->PushRelation(relation);
    return relation;
}

bool DiagramEntity::RemoveRelationFromVector(RelationEntity *entity)
{
    for (auto relation : this->relations)
    {
        if (relation == entity)
        {
            this->relations.erase(std::find(this->relations.begin(), this->relations.end(), relation));
            return true;
        }
    }
    return false;
}

std::string DiagramEntity::GetName()
{
    return this->name;
}

const long DiagramEntity::GetId()
{
    return this->ID;
}

void DiagramEntity::SetName(std::string name)
{
    this->name = name;
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

DiagramEntity::~DiagramEntity()
{
    // Cascade delete of attributes
    for (auto attrib : this->attributes)
    {
        delete attrib;
    }

    // Cascade delete of relations
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