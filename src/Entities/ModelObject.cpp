#include "ModelObject.h"

void ModelObject::ChangePosition(int pos_x, int pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

int ModelObject::GetPosX(){
    return this->pos_x;
}

int ModelObject::GetPosY(){
    return this->pos_y;
}
