#include "DiagramEntity.h"
#include "RelationEntity.h"
#include "../Common/enums.h"
#include <iostream>

int main()
{
    DiagramEntity de = DiagramEntity("haha");
    std::cout << de.GetName() << std::endl;

    de.AddAttrib("pica");
    DiagramEntity de2 = DiagramEntity("lala");

    auto re = de.AddRelation(de2);

    return 0;
}

/*
class B;

class A
{
private:
    B *b_instance;

public:
    A(int);
};

class B
{
private:
    int x;
    A a_instance;

public:
    B(int);
};

A::A(int x) : b_instance(new B(x)) {}

B::B(int x) : x(x), a_instance(x) {}

int main()
{
}
*/