#include "AttributeEntity.h"
#include "../Common/enums.h"
#include <string>

AttributeEntity::AttributeEntity(Enums::Attrib_type type, std::string data)
    : type(type), data(data), access(Enums::AccessModifiers::public_)
{
}

void AttributeEntity::SetData(std::string data)
{
    this->data = data;
}

Enums::Attrib_type AttributeEntity::GetType(){
    return this->type;
}

std::string AttributeEntity::GetData(){
    return this->data;
}

void AttributeEntity::SwitchType()
{
    this->type = (this->type == Enums::Attrib_type::field) ? this->type = Enums::Attrib_type::method : Enums::Attrib_type::field;
}

void AttributeEntity::SetAccess(Enums::AccessModifiers access)
{
    this->access = access;
}
Enums::AccessModifiers AttributeEntity::GetAccess()
{
    return access;
}

bool AttributeEntity::IsOK()
{
    int count = 0;
    for(auto c : data)
    {
        if(c == ' ')
            count++;
    }
    if(count != 1 || data[0] == ' ' || data[data.length() - 1] == ' ')
        return false;
    return true;
}

bool AttributeEntity::IsMethod()
{
    std::string brackets = "";
    int brackets_found = 0;
    for(auto c : data)
    {
        if((c == ')' && brackets_found == 0) || (c == '(' && brackets_found == 1))
            break;
        if(c == '(' || c == ')')
            brackets_found++;
        if(brackets_found == 1 && c != ')')
                brackets = brackets + c;
    }
    if(data[data.length() - 1] != ')' || brackets_found != 2)
        return false;
    return true;
}

AttributeEntity::~AttributeEntity()
{
}
