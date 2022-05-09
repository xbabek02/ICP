#include "enums.h"
#include "string.h"

const char* Enums::CardinalityToLiteral(Enums::Cardinalities c){
    if (c == Enums::Cardinalities::one)
        return "one";
    else if (c == Enums::Cardinalities::zero_to_n)
        return "zero_to_n";
    else if (c == Enums::Cardinalities::one_to_n)
        return "one_to_n";
    else
        return "none";
}

const char* Enums::TypeToLiteral(Enums::RelationTypes t){
    if (t == Enums::RelationTypes::agregation)
        return "agregation";
    else if (t == Enums::RelationTypes::generalisation)
        return "generalisation";
    else if (t == Enums::RelationTypes::composition)
        return "composition";
    else
        return "asociation";
}

Enums::RelationTypes Enums::LiteralToType(const char* t){
    if (!strcmp(t, "agregation"))
        return Enums::RelationTypes::agregation;
    else if (!strcmp(t, "generalisation"))
        return Enums::RelationTypes::generalisation;
    else if (!strcmp(t, "composition"))
        return Enums::RelationTypes::composition;
    else
        return Enums::RelationTypes::asociation;
}

Enums::Cardinalities Enums::LiteralToCardinality(const char* c){
    if (!strcmp(c, "one"))
        return Enums::Cardinalities::one;
    else if (!strcmp(c, "zero_to_n"))
        return Enums::Cardinalities::zero_to_n;
    else if (!strcmp(c, "one_to_n"))
        return Enums::Cardinalities::one_to_n;
    else
        return Enums::Cardinalities::none;
}

const char*Enums::AccessModifierToLiteral(Enums::AccessModifiers am){
    if (am == Enums::AccessModifiers::package_)
        return "package";
    else if (am == Enums::AccessModifiers::private_)
        return "private";
    else if (am == Enums::AccessModifiers::protected_)
        return "protected";
    else
        return "public";
}

Enums::AccessModifiers Enums::LiteralToAccessModifier(const char*c){
    if (!strcmp(c, "package"))
        return Enums::AccessModifiers::package_;
    else if (!strcmp(c, "private"))
        return Enums ::AccessModifiers::private_;
    else if (!strcmp(c, "protected"))
        return Enums::AccessModifiers::protected_;
    else
        return Enums::AccessModifiers::public_;
}



