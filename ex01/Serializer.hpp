#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <iostream>
#include <string>
#include <stdint.h>

/**
 * [...., char(8bit), short(16bit), int(32bit) ]
 * のように値を埋める
 */
struct Data
{
    char c;
    short s;
    int i;
};
uintptr_t serialize(Data *ptr);
Data *deserialize(uintptr_t raw);

#endif
