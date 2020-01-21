#ifndef DESERTBIOME_H
#define DESERTBIOME_H

#include "Biome.h"
#include "../../Chunk/Chunk.h"

class DesertBiome : public Biome {
    public:
        DesertBiome() ;

        BlockId getTopBlock() const override;
        BlockId getUnderWaterBlock() const override;
        BlockId getStoneBlock() const;
        void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const override;
        BlockId getPlant(Rand& rand) const override;

    private:
        NoiseParameters getNoiseParameters() override;
};

#endif // DESERTBIOME_H
