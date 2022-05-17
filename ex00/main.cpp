#include <iostream>
#include "Converter.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "invalid args" << std::endl;
        return 1;
    }
    Converter converter(argv[1]);
    converter.convert();
    return 0;
}
