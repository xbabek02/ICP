#include "RelationEntity.h"
#include "DiagramEntity.h"
#include "../Common/enums.h"

#include <iostream>
#include <string>

int RelationEntity::ID_generator = 1;

RelationEntity::RelationEntity(std::string name, DiagramEntity *first, DiagramEntity *second,
                               Enums::RelationTypes type, Enums::RelationSide side,
                               Enums::Cardinalities c1, Enums::Cardinalities c2,
                               int node1, int node2, int distance)
    : ID(ID_generator++), relation_name(name), first(first), second(second), relation_diagramEntity(nullptr),
       cardinality1(c1), cardinality2(c2), type(type), side(side), node1(node1), node2(node2), distance(distance)
{\
    enitites = std::make_pair(first, second);
    cardinalities = std::make_pair(cardinality1, cardinality2);
}

RelationEntity::RelationEntity(DiagramEntity *first, DiagramEntity *second)
    : ID(ID_generator), relation_name("<<empty " + std::to_string(ID_generator) + ">>"),
      first(first), second(second),
      relation_diagramEntity(nullptr),
      cardinality1(Enums::Cardinalities::one), cardinality2(Enums::Cardinalities::one),
      type(Enums::RelationTypes::asociation), side(Enums::RelationSide::first),
      node1(0), node2(0)

{
    enitites = std::make_pair(first, second);
    cardinalities = std::make_pair(cardinality1, cardinality2);
    ID_generator++;
}

void RelationEntity::SwitchRelationSide()
{
    side = (side == Enums::RelationSide::first) ? Enums::RelationSide::second : Enums::RelationSide::first;
}

Enums::RelationSide RelationEntity::GetSide(){
    return this->side;
}

Enums::RelationTypes RelationEntity::GetType(){
    return this->type;
}

void RelationEntity::SetRelationType(Enums::RelationTypes type){
    this->type = type;
}

void RelationEntity::AddRelationEntity(DiagramEntity *relationEntity)
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

void RelationEntity::ChangeCardinality1(Enums::Cardinalities arg)
{
    this->cardinality1 = arg;
}

void RelationEntity::ChangeCardinality2(Enums::Cardinalities arg)
{
    this->cardinality2 = arg;
}

int RelationEntity::GetNode1(){
    return this->node1;
}

int RelationEntity::GetNode2(){
    return this->node2;
}

int RelationEntity::GetDistance(){
    return this->distance;
}

void RelationEntity::ChangeNode1(int node){
    this->node1 = node;
}

void RelationEntity::ChangeNode2(int node){
    this->node2 = node;
}

void RelationEntity::ChangeDistance(int distance){
    this->distance = distance;
}

int RelationEntity::GetId()
{
    return this->ID;
}

std::pair<Enums::Cardinalities, Enums::Cardinalities> RelationEntity::GetCardinalities(){
    return this->cardinalities;
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
