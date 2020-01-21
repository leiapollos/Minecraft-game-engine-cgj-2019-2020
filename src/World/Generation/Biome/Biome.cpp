#include "Biome.h"

Biome::Biome(const NoiseParameters& parameters, int treeFreq, int plantFreq)
    : m_treeFreq (treeFreq), m_plantFreq(plantFreq) {
    m_heightGenerator.setParameters(parameters);
}

BlockId Biome::getBeachBlock() const {
    return BlockId::SAND;
}

BlockId Biome::getStoneBlock() const {
    return BlockId::STONE;
}

int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const {
    return m_heightGenerator.generateHeight((float)(x+chunkX), (float)(z+chunkZ));
}

int Biome::getTreeFrequency() const noexcept {
    return m_treeFreq;
}

int Biome::getPlantFrequency() const noexcept {
    return m_plantFreq;
}

