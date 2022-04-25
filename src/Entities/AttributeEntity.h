#ifndef __ATTRIBUTE_ENTITY_H__
#define __ATTRIBUTE_ENTITY_H__

#include "../Common/enums.h"

#include <string>

class AttributeEntity
{
private:
    Enums::Attrib_type type;
    std::string data;

public:
    AttributeEntity();
    AttributeEntity(Enums::Attrib_type, std::string);
    ~AttributeEntity();
};

#endif