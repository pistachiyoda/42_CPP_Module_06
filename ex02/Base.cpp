#include "Base.hpp"

Base::~Base()
{}

Base *generate()
{
    int i = rand();
    if (i % 3 == 2)
        return new A;
    if (i % 3 == 1)
        return new B;
    return new C;
}
