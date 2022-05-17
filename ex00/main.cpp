#include <iostream>
#include "Converter.hpp"

/**
 * TBD
 * - オーバーフロー
 * - Infinite
 * - Nan
 */

/**
 * 受け取れる値
 * 表示可能な一文字(char)
 * intのリテラルの数値
 * floatのリテラルの数値
 * inf, +inf, -inf
 * inff, +inff, -inff
 */
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
