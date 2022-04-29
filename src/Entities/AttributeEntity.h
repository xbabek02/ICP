#ifndef __ATTRIBUTE_ENTITY_H__
#define __ATTRIBUTE_ENTITY_H__

#include "../Common/enums.h"

#include <string>

/**
 * @brief The AttributeEntity class
 * Is responsible for attribute storage
 * Attribute can be either field or a method
 * Attributes are stored inside of RelationEntity in the relations vector
 */
class AttributeEntity
{
private:
    Enums::Attrib_type type;
    std::string data;

public:
    void SetData(std::string);
    std::string GetData();
    void SwitchType();
    Enums::Attrib_type GetType();
    AttributeEntity(Enums::Attrib_type, std::string);
    ~AttributeEntity();
};

#endif
