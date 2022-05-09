#ifndef ITEMVISIBILITY_H
#define ITEMVISIBILITY_H


#include <map>

class ItemVisibility
{
public:
    ItemVisibility();
    bool Visible();
    void SetDependency(int instance_id, bool value);

private:
    //if all values all false, item is visible
    std::map<int, bool> visibility_dependencies;
};

#endif // ITEMVISIBILITY_H
