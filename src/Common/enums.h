/**
 * @file enums.h
 * @author Radomír Bábek, Martin Ohnút (xbabek02, xohnut01)
 * @brief Enums used by all over the program
 * @version 0.1
 * @date 2022-05-09
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef __ENUMS_H__
#define __ENUMS_H__

namespace Enums
{
    enum Cardinalities
    {
        one,
        zero_to_n,
        one_to_n,
        none
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
    enum AccessModifiers
    {
        public_,
        private_,
        protected_,
        package_
    };
    enum MessageTypes
    {
        sync,
        async,
        returnal,
        constructing,
        desctructing
    };

    const char *CardinalityToLiteral(Cardinalities c);
    const char *TypeToLiteral(RelationTypes t);
    Cardinalities LiteralToCardinality(const char *c);
    RelationTypes LiteralToType(const char *t);
    const char *AccessModifierToLiteral(AccessModifiers am);
    AccessModifiers LiteralToAccessModifier(const char *c);
}

#endif
