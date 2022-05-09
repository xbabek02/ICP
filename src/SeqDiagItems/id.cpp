#include "idcls.h"

int IDcls::ID_generator = 1;

IDcls::IDcls() :
    ID(ID_generator++)
{

}

IDcls::IDcls(const IDcls &item)
{
    ID = item.ID;
}

bool IDcls::operator==(IDcls &second)
{
    if (ID == second.ID){
        return true;
    }
    return false;
}

void IDcls::SetID_generator(int value)
{
    ID_generator = value;
}

void IDcls::SetID(int id)
{
    ID = id;
}

int IDcls::GetID()
{
    return ID;
}

