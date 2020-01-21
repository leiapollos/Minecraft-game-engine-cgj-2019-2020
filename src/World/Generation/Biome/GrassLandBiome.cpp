#include "GrassLandBiome.h"

GrasslandBiome::GrasslandBiome()
    :   Biome  (getNoiseParameters(), 1300, 800) {

}

BlockId GrasslandBiome::getTopBlock() const {
    return BlockId::GRASS;
}

BlockId GrasslandBiome::getUnderWaterBlock() const {
    return BlockId::SAND;
}

BlockId GrasslandBiome::getBeachBlock () const {
    return BlockId::DIRT;
}

BlockId GrasslandBiome::getStoneBlock() const {
    return BlockId::STONE;
}
void GrasslandBiome::makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const {
    int height = rand.intInRange(2, 5);
    int leafeSize = 1;
    for (int i = y; i < y+height; i++) {
	    chunk.setBlock(x, i, z, chunk.getBlockId(BlockId::WOOD));
    }
	for (int i = -leafeSize; i <= leafeSize; i++)
		for (int j = -leafeSize; j <= leafeSize; j++)
			for (int k = height; k <= height+1; k++) {
                chunk.setBlock(x + i, y + k, z + j, chunk.getBlockId(BlockId::LEAVES));
			}
    chunk.setBlock(x, y + height + 2, z, chunk.getBlockId(BlockId::LEAVES));
}

BlockId GrasslandBiome::getPlant(Rand& rand) const {
    return rand.intInRange(0, 10) > 6 ? BlockId::ROSE : BlockId::TALLGRASS;
}

NoiseParameters GrasslandBiome::getNoiseParameters() {
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 1.20f;
    heightParams.smooth = 0.01f;
    heightParams.offset = 0;
    heightParams.minHeight = 0;
    heightParams.persistance = 0.41f;
    heightParams.maxHeight = (int)150.0f;
    return heightParams;
}