#ifndef WORLD_HPP
#define WORLD_HPP

#include <stdint.h>

typedef struct world_s
{
    uint32_t publicSeed;
    uint32_t privateSeed;
    void*    players;
    void*    planets;
} world_t;

#endif