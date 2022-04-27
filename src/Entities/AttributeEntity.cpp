#include "AttributeEntity.h"
#include "../Common/enums.h"
#include <string>

AttributeEntity::AttributeEntity(Enums::Attrib_type type, std::string data)
    : type(type), data(data)
{
}

void AttributeEntity::SetData(std::string data)
{
    this->data = data;
}

void AttributeEntity::SwitchType()
{
    this->type = (this->type == Enums::Attrib_type::field) ? this->type = Enums::Attrib_type::method : Enums::Attrib_type::field;
}

AttributeEntity::~AttributeEntity()
{
}
