#include "DesertBiome.h"
#include "../../WorldConstants.h"

DesertBiome::DesertBiome() : Biome(getNoiseParameters(), 1000, 800) {}

BlockId DesertBiome::getTopBlock() const {
    return BlockId::SAND;
}

BlockId DesertBiome::getStoneBlock() const {
    return BlockId::SAND;
}

BlockId DesertBiome::getUnderWaterBlock() const {
    return BlockId::SAND;
}


void DesertBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const {
    int height = rand.intInRange(2, 5);
    for(int i = y; i < y+height; i++)
        chunk.setBlock(x,i,z, BlockId::CACTUS);
}

BlockId DesertBiome::getPlant(Rand& rand) const {
    return BlockId::DEADSHRUB;
}

NoiseParameters DesertBiome::getNoiseParameters() {
    NoiseParameters heightParams;
    heightParams.octaves = 9; //4
    heightParams.smooth = 0.001f; //0.01f
    heightParams.maxHeight = 120; // 150
    heightParams.minHeight = 0;
    heightParams.persistance = 0.55f; // 0.5f
    heightParams.offset = 0; // 0
    heightParams.amplitude = 1.4f; // 1.0f
    return heightParams;
}
