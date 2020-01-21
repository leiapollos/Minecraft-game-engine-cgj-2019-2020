#ifndef BIOME_H
#define BIOME_H

#include "../../../NoiseGenerator.h"
#include "../../Block/BlockId.h"
#include "../../../Utils/Random.h"
#include "../../Chunk/Chunk.h"
class Chunk;
using Rand = Random<std::minstd_rand>;
struct Biome {
    public:
        Biome(const NoiseParameters& parameters, int treeFreq, int plantFreq);
        virtual ~Biome() = default;

        virtual BlockId getTopBlock() const = 0;
        virtual BlockId getUnderWaterBlock() const = 0;
        virtual BlockId getBeachBlock() const;
        virtual BlockId getStoneBlock() const;
        virtual void makeTree(Rand& rand, Chunk& chunk, int x, int y, int z) const = 0;
        virtual BlockId getPlant(Rand& rand) const = 0;


        int getHeight(int x, int z, int chunkX, int chunkZ) const;
        int getTreeFrequency() const noexcept;
        int getPlantFrequency() const noexcept;

    protected:
        virtual NoiseParameters getNoiseParameters() = 0;

    private:
        NoiseGenerator m_heightGenerator;
        int m_treeFreq;
        int m_plantFreq;
};

#endif // BIOME_H
