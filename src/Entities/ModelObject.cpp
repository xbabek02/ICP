#include "ModelObject.h"

ModelObject::ModelObject(){};

void ModelObject::ChangePosition(int pos_x, int pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

DiagramEntity *ModelObject::GetData()
{
    return this->entity;
}
