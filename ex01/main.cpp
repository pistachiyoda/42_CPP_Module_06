#include "Serializer.hpp"
#include <limits>

int main()
{
    Data *d = new Data;
    d->c = 'c';
    d->s = 1;
    d->i = 1; 
    uintptr_t raw = serialize(d);
    std::cout << raw << std::endl;
    delete d;
    Data *deserialized = deserialize(raw);
    std::cout << "c: " << deserialized->c << std::endl;
    std::cout << "s: " << deserialized->s << std::endl;
    std::cout << "i: " << deserialized->i << std::endl;
    delete deserialized;
    return (0);
}
