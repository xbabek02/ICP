#include <vector>
#include <string>
#include <new>
#include <iostream>
#include <algorithm>

#include "RelationEntity2.h"
#include "DiagramEntity.h"
#include "../Common/enums.h"
#include "AttributeEntity.h"
#include "../ClsDiagItems/connection.h"

int DiagramEntity::ID_generator = 1;

DiagramEntity::DiagramEntity(std::string name) : ID(ID_generator), name(name)
{
    ID_generator++;
}

DiagramEntity::DiagramEntity() : ID(ID_generator), name("Entity " + std::to_string(ID_generator))
{
    ID_generator++;
}

void DiagramEntity::ChangePosition(int pos_x, int pos_y)
{
    ModelObject::ChangePosition(pos_x, pos_y);
}

QList<AttributeEntity*> DiagramEntity::GetMethods()
{
    QList<AttributeEntity*> methods;
    for(auto attribute : attributes)
    {
        if(attribute->IsMethod() && attribute->IsOK())
            methods.append(attribute);
    }
    return methods;
}

AttributeEntity *DiagramEntity::FindAttributeByData(QString data)
{
    for(auto attribute : attributes)
    {
        if(QString::fromStdString(attribute->GetData()) == data)
            return attribute;
    }
    return nullptr;
}

void DiagramEntity::AddSeqDiagramInstace(InstanceEntity *instace)
{
    seqDiagramInstances.append(instace);
}

void DiagramEntity::RemoveSeqDiagramInstace(InstanceEntity *instace)
{
    if(seqDiagramInstances.empty() == true)
        return;
    for(int i {0}; i < seqDiagramInstances.count(); i++)
    {
        if(seqDiagramInstances[i] == instace)
        {
            seqDiagramInstances.removeAt(i);
        }
    }
}

void DiagramEntity::SetDiagramItem(ClassDiagramItem *item)
{
    this->thisDiagramItem = item;
}

QList<InstanceEntity*> DiagramEntity::GetSeqDiagramInstances()
{
    return seqDiagramInstances;
}

ClassDiagramItem *DiagramEntity::GetDiagramItem()
{
    return thisDiagramItem;
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

inline void DiagramEntity::SwitchAttribTypeAt(std::size_t index)
{
    attributes.at(index)->SwitchType();
}

inline void DiagramEntity::UpdateAttribAt(std::size_t index, std::string new_data)
{
    attributes.at(index)->SetData(new_data);
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

void DiagramEntity::SetWidth(int value)
{
    width = value;
}

int DiagramEntity::GetWidth()
{
    return width;
}

int DiagramEntity::GetFirstMethodIndex()
{
    return firstMethodIndex;
}

void DiagramEntity::SetFirstMethodIndex(int value)
{
    firstMethodIndex = value;
}

void DiagramEntity::RemoveAttribAt(std::size_t index)
{
    if (attributes.size() <= index)
    {
        return;
    }
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
                                              Enums::RelationTypes type, Enums::RelationSide site,
                                              Enums::Cardinalities cardinality1, Enums::Cardinalities cardinality2, Model *m,
                                              int node1, int node2, int distance)
{
    RelationEntity *relation;
    try
    {
        relation = new RelationEntity(name, this, &entity, type, site, cardinality1, cardinality2, node1, node2, distance);
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

int DiagramEntity::GetId()
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

AttributeEntity*DiagramEntity::GetAttribAt(std::size_t index){
    return this->attributes.at(index);
}

std::string DiagramEntity::GetAttributeName(int index)
{
    return this->attributes.at(index)->GetData();
}

std::size_t DiagramEntity::AttribCount(){
    return this->attributes.size();
}

QList<Connection*> DiagramEntity::GetRelationViewItems()
{
    QList<Connection*> connections;
    for (auto relation : this->relations)
    {
        connections.append(relation->GetViewItem());
    }
    return connections;
}

ClassDiagramItem *DiagramEntity::GetView()
{
    return thisDiagramItem;
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
        {
            delete relation;
        }
        else
        {
            DiagramEntity *second = ((*this == *res.first) ? res.second : res.first);
            auto it = std::remove_if(second->relations.begin(), second->relations.end(),
                                     [relation](RelationEntity* a)
                                     { return a == relation; });
            second->relations.erase(it, second->relations.end());
            delete relation;
        }
    }
    if (thisDiagramItem){
        delete thisDiagramItem;
    }

}
