#ifndef __ENUMS_H__
#define __ENUMS_H__

namespace Enums
{
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
    enum RelationSide
    {
        first,
        second
    };

    const char*CardinalityToLiteral(Cardinalities c);
    const char*TypeToLiteral(RelationTypes t);
    Cardinalities LiteralToCardinality(const char* c);
    RelationTypes LiteralToType(const char* t);
}


#endif
