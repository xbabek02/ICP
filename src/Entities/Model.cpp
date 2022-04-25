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

ModelObject *Model::CreateEntity(std::string name)
{
    auto mo = Model::CreateEntity();
    if (mo == nullptr)
    {
        return nullptr;
    }
    for (auto entity : this->entities)
    {
        if (entity->GetData()->GetName() == name)
        {
            throw Model::NameExistsException();
        }
    }
    mo->GetData()->SetName(name);
    return mo;
}

ModelObject *Model::CreateEntity(std::string name, int pos_x, int pos_y)
{
    auto mo = Model::CreateEntity();
    auto mo = Model::CreateEntity(name);

    mo->ChangePosition(pos_x, pos_y);
    return mo;
}

ModelObject *Model::GetByName(std::string name)
{
    for (auto entity : Model::entities)
    {
        if (entity->GetData()->GetName() == name)
        {
            return entity;
        }
    }
    return nullptr;
}

bool Model::DeleteByName(std::string name)
{
    for (auto entity : Model::entities)
    {
        if (entity->GetData()->GetName() == name)
        {
            this->DeleteEntity(entity);
        }
    }
}

void Model::DeleteEntity(ModelObject *entity)
{
    this->entities.erase(std::find(this->entities.begin(), this->entities.end(), entity));
    delete entity->GetData();
    delete entity;
}

ModelObject *Model::CreateEntity()
{
    ModelObject *mo;
    try
    {
        mo = new ModelObject();
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "bad_alloc detected: " << e.what();
        // to be caught later
        throw Model::AllocException();
    }
    mo->ChangePosition(Model::default_pos_x, Model::default_pos_y);
    try
    {
        DiagramEntity **data_destination;
        *data_destination = mo->GetData();
        *data_destination = new DiagramEntity();
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "bad_alloc detected: " << e.what();
        delete mo;
        // to be caught later
        throw Model::AllocException();
    }
    this->entities.push_back(mo);
    return mo;
}

Model::~Model()
{
    for (auto entity : this->entities)
    {
        delete entity->GetData();
        delete entity;
    }
}
