#ifndef HASH_HPP
#define HASH_HPP

#include <stdint.h>

uint32_t Hash32(uint32_t a, uint32_t b, uint32_t c)
{
    // Never ever touch this
    // please
    a *= 719079523U;
    a ^= b;
    b *= 322361659U;
    b ^= c;
    return (a * b) ^ c;
}

#endif // HASH_HPP