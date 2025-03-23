#pragma once
#include <string>
#include "driver.h"


inline std::string fetchstring(std::uint64_t address)
{
    std::string result;
    char character;
    int offset = 0;

    if (read<int>(address + 0x18) >= 16u)
        address = read<std::uint64_t>(address);

    while ((character = read<char>(address + offset)) != 0)
    {
        result.push_back(character);
        offset += sizeof(character);
    }

    return result;
}
