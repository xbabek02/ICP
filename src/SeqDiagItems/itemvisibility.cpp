#include "itemvisibility.h"


ItemVisibility::ItemVisibility()
{

}

bool ItemVisibility::Visible()
{
    for (const auto& kv : visibility_dependencies) {
        if (kv.second) {
            return false;
        }
    }
    return true;
}

void ItemVisibility::SetDependency(int instance_id, bool value)
{
    visibility_dependencies[instance_id] = value;
}
