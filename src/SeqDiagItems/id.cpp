/**
 * @file id.cpp
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief File that contains class for id operations, to be inherited by instances
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "idcls.h"

int IDcls::ID_generator = 1;

IDcls::IDcls() : ID(ID_generator++)
{
}

IDcls::IDcls(const IDcls &item)
{
    ID = item.ID;
}

bool IDcls::operator==(IDcls &second)
{
    if (ID == second.ID)
    {
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
