#ifndef __MODEL_OBJECT_H
#define __MODEL_OBJECT_H


/**
 * @brief The ModelObject class
 * Has responsibility of positioning of elements
 */
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
