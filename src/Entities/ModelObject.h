#ifndef __MODEL_OBJECT_H
#define __MODEL_OBJECT_H

#include "DiagramEntity.h"
#include "RelationEntity.h"

class ModelObject
{
private:
    int pos_x;
    int pos_y;
    DiagramEntity *entity;

public:
    ModelObject();
    void ChangePosition(int, int);
    DiagramEntity *GetData();
};

#endif