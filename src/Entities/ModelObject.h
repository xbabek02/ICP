/**
 * @file ModelObject.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Interface for working with possitions of elements
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __MODEL_OBJECT_H
#define __MODEL_OBJECT_H

class ModelObject
{
private:
    int pos_x;
    int pos_y;

public:
    void ChangePosition(int, int);
    int GetPosX();
    int GetPosY();
};

#endif
