#ifndef BLOCKID_H
#define BLOCKID_H

#include <cstdint>

using Block_t = uint8_t;

enum class BlockId : Block_t {
    GRASS = 0, 
    DIRT = 1, 
    STONE = 2, 
    AIR = 3, 
    LEAVES = 4, 
    WOOD = 5, 
    WOODBASE = 6, 
    DIAMOND = 7, 
    REDSTONE = 8, 
    BEDROCK = 9, 
    WATER = 10,
    GLASS = 11,
    SAND = 12,
    CACTUS = 13,
    DEADSHRUB = 14,
    ROSE = 15,
    TALLGRASS = 16,
    NUM_TYPES
};

#endif