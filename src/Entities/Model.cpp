#include "DiagramEntity.h"
#include "RelationEntity.h"
#include "Model.h"
#include "ModelObject.h"

#include <new>
#include <iostream>
#include <algorithm>

int Model::default_pos_x = 0;
int Model::default_pos_y = 0;

Model::Model()
{
}

DiagramEntity *Model::CreateEntity()
{
    DiagramEntity *de;
    try
    {
        de = new DiagramEntity();
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "bad_alloc detected: " << e.what();
        // to be caught later
        throw Model::AllocException();
    }
    de->ChangePosition(Model::default_pos_x, Model::default_pos_y);
    this->entities.push_back(de);
    return de;
}

DiagramEntity *Model::CreateEntity(std::string name)
{
    auto me = Model::CreateEntity();
    if (me == nullptr)
    {
        return nullptr;
    }
    for (auto entity : this->entities)
    {
        if (entity->GetName() == name)
        {
            throw Model::NameExistsException();
        }
    }
    me->SetName(name);
    return me;
}

DiagramEntity *Model::CreateEntity(std::string name, int pos_x, int pos_y)
{
    auto me = Model::CreateEntity(name);
    if (me == nullptr)
    {
        return nullptr;
    }
    me->ChangePosition(pos_x, pos_y);
    return me;
}

void Model::PushRelation(RelationEntity *entity)
{
    this->relations.push_back(entity);
}

RelationEntity *Model::CreateRelation(DiagramEntity &e1, DiagramEntity &e2)
{
    return e1.CreateRelation(e2, this);
}
RelationEntity *Model::CreateRelation(std::string name, DiagramEntity &e1, DiagramEntity &e2,
                                      Enums::RelationTypes type, Enums::RelationSite site,
                                      Enums::Cardinalities c1, Enums::Cardinalities c2)
{
    return e1.CreateRelation(name, e2, type, site, c1, c2, this);
}

DiagramEntity *Model::GetEntityById(long Id)
{
    for (auto entity : Model::entities)
    {
        if (entity->GetId() == Id)
        {
            return entity;
        }
    }
    return nullptr;
}

bool Model::DeleteEntityById(long Id)
{
    for (auto entity : Model::entities)
    {
        if (entity->GetId() == Id)
        {
            DeleteEntity(entity);
            return true;
        }
    }
    return false;
}

void Model::DeleteEntity(DiagramEntity *entity)
{
    this->entities.erase(std::find(this->entities.begin(), this->entities.end(), entity));
    delete entity;
}

bool Model::DeleteRelationById(long Id)
{
    for (auto relation : this->relations)
    {
        if (relation->GetId() == Id)
        {
            DeleteRelation(relation);
            return true;
        }
    }
    return false;
}

RelationEntity *Model::GetRelationById(long Id)
{
    for (auto relation : this->relations)
    {
        if (relation->GetId() == Id)
        {
            return relation;
        }
    }
    return nullptr;
}

void Model::DeleteRelation(RelationEntity *relation)
{
    this->relations.erase(std::find(this->relations.begin(), this->relations.end(), relation));
    delete relation;
}

Model::~Model()
{
    for (auto entity : this->entities)
    {
        delete entity;
    }
}
