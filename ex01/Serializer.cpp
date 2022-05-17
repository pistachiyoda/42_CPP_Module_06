#include "Serializer.hpp"

uintptr_t serialize(Data *ptr)
{
    uintptr_t raw = 0;
    raw += ptr->c;
    raw <<= 16;
    raw += ptr->s;
    raw <<= 32;
    raw += ptr-> i;
    return raw;
}

Data *deserialize(uintptr_t raw)
{
    Data *d = new Data;
    d->i = static_cast<int>(raw);
    raw >>= 32;
    d->s = static_cast<short>(raw);
    raw >>= 16;
    d->c = static_cast<char>(raw);
    return d;
}