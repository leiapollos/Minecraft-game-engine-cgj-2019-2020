#ifndef CLASSICOVERWORLDGENERATOR_H_INCLUDED
#define CLASSICOVERWORLDGENERATOR_H_INCLUDED

#include "TerrainGenerator.h"

#include "../../Chunk/Chunk.h"
#include "../../WorldConstants.h"
#include "../../../Utils/Array2D.h"
#include "../../../NoiseGenerator.h"
#include "../Biome/Biome.h"
#include "../Biome/GrassLandBiome.h"
#include "../Biome/DesertBiome.h"
#include "../../../mathf.h"
class Chunk;

class ClassicWorldGenerator : public TerrainGenerator {
    public:
        ClassicWorldGenerator();
        void generateTerrainFor     (Chunk& chunk)      override;
        int  getMinimumSpawnHeight  () const noexcept   override;

    private:
        static void setUpNoise();
        Random<std::minstd_rand> m_random;
        void setBlocks(int maxHeight);

        void getHeightIn (int xMin, int zMin, int xMax, int zMax);
        void getHeightMap();
        void getBiomeMap ();
        const Biome& getBiome(int x, int z) const;
        static NoiseGenerator m_noiseGen;
        GrasslandBiome          m_grassBiome;
        DesertBiome             m_desertBiome;
        //const Biome& getBiome(int x, int z) const;
        Array2D<int, CHUNK_SIZE>        m_heightMap;
        Array2D<int, CHUNK_SIZE + 1>    m_biomeMap;
        Chunk* m_pChunk = nullptr;
};

#endif // CLASSICOVERWORLDGENERATOR_H_INCLUDED