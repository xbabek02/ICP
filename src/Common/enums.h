#ifndef __ENUMS_H__
#define __ENUMS_H__

class Enums
{
public:
    enum Cardinalities
    {
        none,
        one,
        zero_to_n,
        one_to_n
    };
    enum RelationTypes
    {
        asociation,
        composition,
        agregation,
        generalisation,
    };
    enum Attrib_type
    {
        field,
        method
    };
    enum RelationSite
    {
        first,
        second
    };
};

#endif
