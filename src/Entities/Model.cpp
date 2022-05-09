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
                                      Enums::RelationTypes type, Enums::RelationSide side,
                                      Enums::Cardinalities c1, Enums::Cardinalities c2,
                                      int node1, int node2, int distance)
{
    return e1.CreateRelation(name, e2, type, side, c1, c2, this, node1, node2, distance);
}

RelationEntity *Model::CreateRelationById(std::string name, long id1, long id2,
                                          Enums::RelationTypes type, Enums::RelationSide side,
                                          Enums::Cardinalities c1, Enums::Cardinalities c2,
                                          int node1, int node2, int distance)
{
    auto ent1 = GetEntityById(id1);
    auto ent2 = GetEntityById(id2);

    return CreateRelation(name, *ent1, *ent2, type, side, c1, c2, node1, node2, distance);
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

std::vector<DiagramEntity*> &Model::GetEntities()
{
    return entities;
}

std::vector<RelationEntity*> Model::GetRelations()
{
    return relations;
}

void Model::DeleteRelation(RelationEntity *relation)
{
    this->relations.erase(std::find(this->relations.begin(), this->relations.end(), relation));
    delete relation;
}

void Model::SetScene(QGraphicsScene *scene)
{
    this->scene = scene;
}

QGraphicsScene *Model::GetScene()
{
    return scene;
}

AttributeEntity *Model::GetAttributeEntityByName(DiagramEntity *de, std::string name)
{
    for (std::size_t i = 0; i < de->AttribCount(); i++){
        if (de->GetAttributeName(i) == name){
            return de->GetAttribAt(i);
        }
    }
}

void Model::SetUndoStack(QUndoStack *undoStack)
{
    this->undoStack = undoStack;
}

QUndoStack *Model::GetUndoStack()
{
    return this->undoStack;
}

Model::~Model()
{
    for (auto entity : this->entities)
    {
        delete entity;
    }
}
