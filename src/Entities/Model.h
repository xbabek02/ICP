#ifndef __MODEL_H__
#define __MODEL_H__

#include "DiagramEntity.h"
#include "RelationEntity.h"
#include "ModelObject.h"

#include <vector>

class Model
{
private:
    static int default_pos_x;
    static int default_pos_y;
    static const int max_pos_x = INT32_MAX; // need to be updated
    static const int max_pos_y = INT32_MAX;

    std::vector<ModelObject *> entities;

public:
    ModelObject *CreateEntity();
    ModelObject *CreateEntity(std::string);
    ModelObject *CreateEntity(std::string, int, int);
    ModelObject *GetByName(std::string);
    void DeleteEntity(ModelObject *);
    bool DeleteByName(std::string);

    Model();
    ~Model();

    // exceptions
    class NameExistsException
    {
    };
    class AllocException
    {
    };
};

#endif