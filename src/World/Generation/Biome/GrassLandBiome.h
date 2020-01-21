#ifndef GRASSLANDBIOME_H
#define GRASSLANDBIOME_H

#include "Biome.h"

class GrasslandBiome : public Biome {
    public:
        GrasslandBiome();

        BlockId getBeachBlock() const override;
        BlockId getTopBlock() const override;
        BlockId getUnderWaterBlock() const override;
        BlockId getStoneBlock() const;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const override;
        BlockId getPlant(Rand& rand) const override;

    private:
        NoiseParameters getNoiseParameters() override;
};

#endif
