#include "ClassicWorldGenerator.h"

NoiseGenerator ClassicWorldGenerator::m_noiseGen;

ClassicWorldGenerator::ClassicWorldGenerator() { // persistance
    setUpNoise();
}

void ClassicWorldGenerator::setUpNoise() {
    static bool noiseGen = false;
    if (!noiseGen) {
        noiseGen = true;
        NoiseParameters biomeParmams;
        biomeParmams.octaves = 4;
        biomeParmams.smooth = 0.01f;
        biomeParmams.maxHeight = 150;
        biomeParmams.minHeight = 0;
        biomeParmams.persistance = 0.5f;
        biomeParmams.offset = 0; 
        biomeParmams.amplitude = 4.0f;
        m_noiseGen.setParameters(biomeParmams);
    }
}

void ClassicWorldGenerator::generateTerrainFor(Chunk& chunk) {
    m_pChunk = &chunk;
    getBiomeMap();
    getHeightMap();
    auto maxHeight = m_heightMap.getMaxValue();
    setBlocks(maxHeight% CHUNK_SIZE);
}

int ClassicWorldGenerator::getMinimumSpawnHeight() const noexcept {
    return WATER_LEVEL;
}


float smoothstep(float edge0, float edge1, float x) {
    // Scale, bias and saturate x to 0..1 range
    x = x*x*(3 - 2*x);
    // Evaluate polynomial
    return (edge0 * x) + (edge1 * (1-x));
}

float smoothInterpolation(float bottomLeft, float topLeft, float bottomRight, float topRight,
                          float xMin, float xMax,
                          float zMin, float zMax,
                          float x, float z) {
    float   width               = xMax - xMin,
            height              = zMax - zMin;
    float xValue = 1 - (x-xMin)/width;
    float zValue = 1 - (z-zMin)/height;

    float a = smoothstep(bottomLeft,bottomRight,xValue);
    float b = smoothstep(topLeft,topRight,xValue);
    return  smoothstep(a,b,zValue);
}

float bilinearInterpolation(float bottomLeft, float topLeft, float bottomRight, float topRight,
                            float xMin, float xMax,
                            float zMin, float zMax,
                            float x, float z)
{
    float   width               = xMax - xMin,
            height              = zMax - zMin,

            xDistanceToMaxValue = xMax - x,
            zDistanceToMaxValue = zMax - z,

            xDistanceToMinValue = x - xMin,
            zDistanceToMinValue = z - zMin;

    return 1.0f / (width * height) *
           (
               bottomLeft      *   xDistanceToMaxValue * zDistanceToMaxValue +
               bottomRight     *   xDistanceToMinValue * zDistanceToMaxValue +
               topLeft         *   xDistanceToMaxValue * zDistanceToMinValue +
               topRight        *   xDistanceToMinValue * zDistanceToMinValue
           );
}
void ClassicWorldGenerator::getHeightIn (int xMin, int zMin, int xMax, int zMax) {
     auto getHeightAt = [&](int x, int z) {
        const Biome& biome = getBiome(x, z);

        return biome.getHeight(x, z,
                               (int)m_pChunk->pos.x,
                               (int)m_pChunk->pos.z);
    };

    int bottomLeft  = getHeightAt(xMin, zMin);
    int bottomRight = getHeightAt(xMax, zMin);
    int topLeft     = getHeightAt(xMin, zMax);
    int topRight    = getHeightAt(xMax, zMax);

    for (int x = xMin; x < xMax; ++x)
        for (int z = zMin; z < zMax; ++z) {
            float h = smoothInterpolation((float)bottomLeft, (float)topLeft, (float)bottomRight, (float)topRight,
                                          (float)xMin, (float)xMax,
                                          (float)zMin, (float)zMax,
                                          (float)x, (float)z);

            m_heightMap.get(x, z) = (int)h;
        }
}

void ClassicWorldGenerator::getHeightMap() {
    constexpr static auto HALF_CHUNK    = CHUNK_SIZE / 2;
    constexpr static auto CHUNK         = CHUNK_SIZE;

    getHeightIn(0,          0,          HALF_CHUNK,     HALF_CHUNK);
    getHeightIn(HALF_CHUNK, 0,          CHUNK,          HALF_CHUNK);
    getHeightIn(0,          HALF_CHUNK, HALF_CHUNK,     CHUNK);
    getHeightIn(HALF_CHUNK, HALF_CHUNK, CHUNK,          CHUNK);
}

void ClassicWorldGenerator::getBiomeMap() {
    for (int x = 0; x < CHUNK_SIZE + 1; x++)
        for (int z = 0; z < CHUNK_SIZE + 1; z++) {
            int worldX = (int)(x + (int)m_pChunk->pos.x);
            int worldZ = (int)(z + (int)m_pChunk->pos.z);
            int h = m_noiseGen.generateHeight((float)worldX, (float)worldZ);
            m_biomeMap.get(x, z) = h;

        }
}

void ClassicWorldGenerator::setBlocks(int maxHeight) {
    std::vector<sf::Vector3i> trees;
    std::vector<sf::Vector3i> plants;
    for (int z = 0; z < CHUNK_SIZE; ++z) {
        for (int y = 0; y < CHUNK_SIZE; ++y) {
            for (int x = 0; x < CHUNK_SIZE; ++x) {
                Vector3 _pos((float)x,(float)y,(float)z);
                //int worldX = (int)(x + (int)m_pChunk->pos.x);
                int worldY = (int)(y + (int)m_pChunk->pos.y);
                //int worldZ = (int)(z + (int)m_pChunk->pos.z);
                auto& biome = getBiome(x, z);
                int surfaceHeight = m_heightMap.get(x,z);//m_noiseGen.generateHeight((float)worldX,(float)worldZ);
                
                if(worldY == 0)
                    m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::BEDROCK));
                else if (worldY < 0)
                    m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::AIR));
                //else if (m_noiseGen.fBM3D((float)worldX, (float)worldY, (float)worldZ, 0.1f, 3) < 0.42f)
                //  m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::AIR));
                //else if(worldY <= m_noiseGen.generateStoneHeight((float)worldX,(float)worldZ)) {
                //    if (m_noiseGen.fBM3D ((float)worldX, (float)worldY, (float)worldZ, 0.01f, 2) < 0.2f && worldY < 40)
                //        m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::DIAMOND)); 
                //    else if (m_noiseGen.fBM3D ((float)worldX, (float)worldY, (float)worldZ, 0.03f, 3) < 0.21f && worldY < 20)
                //        m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::REDSTONE)); 
                //    else
                //        m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::STONE));
                //}
                else if (worldY == surfaceHeight) {
                    if (worldY >= WATER_LEVEL) {
                        if (worldY < WATER_LEVEL+4) {
                            m_pChunk->setBlock(_pos, biome.getBeachBlock());
                            continue;
                        }
                        //else if (m_noiseGen.fBM3D((float)worldX, (float)worldY, (float)worldZ, 0.4f, 2) < 0.35f
                        if (m_random.intInRange(0, biome.getTreeFrequency()) == 5
                            /*&& !m_pChunk->checkNeighbourBlocksForId(worldX,worldY,worldZ, BlockId::WOODBASE)*/) {
                            //biome.makeTree(m_random,*m_pChunk,worldX, worldY, worldZ);
                            //m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::WOODBASE));
                            //m_pChunk->setBlock(_pos, biome.getTopBlock());
                            m_pChunk->setBlock(_pos, biome.getTopBlock());
                            trees.emplace_back(x, y, z);
                        }
                        else if (m_random.intInRange(0, biome.getTreeFrequency()) == 5) {
                            //m_pChunk->setBlock(_pos, BlockId::DEADSHRUB);
                            m_pChunk->setBlock(_pos, biome.getTopBlock());
                            //m_pChunk->setBlock(_pos, biome.getTopBlock());
                            //m_pChunk->setBlock(_pos, BlockId::ROSE);
                            plants.emplace_back(x,y,z);
                            //continue;
                            //getBiome(x, z).makePlant(m_random,*m_pChunk, x, y, z);
                        }
                        else{

                            m_pChunk->setBlock(_pos, biome.getTopBlock());
                        }
                    }
                    else {
                        m_pChunk->setBlock(_pos, biome.getUnderWaterBlock()); // underwater
                    }
                }
                else if(worldY < surfaceHeight && worldY > WATER_LEVEL+23)
                    m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::DIRT));
                else if(worldY < surfaceHeight){
                    //m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::STONE));
                    m_pChunk->setBlock(_pos, biome.getStoneBlock());
                }
                else {
                    m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::AIR));//new Air(_pos, this));
                }
                if (worldY < WATER_LEVEL && worldY > WATER_LEVEL-30 && m_pChunk->getBlock(x,y,z) == BlockId::AIR) {
                    m_pChunk->waterChunk = true;
                    m_pChunk->setBlock(_pos, m_pChunk->getBlockId(BlockId::WATER));
                }
            }
        }
    }
    for (auto& tree : trees) {
		int x = (int)tree.x;
		int y = (int)tree.y;
		int z = (int)tree.z;
        getBiome(x, z).makeTree(m_random,*m_pChunk, x, y, z);
        m_pChunk->transparentChunk = true;
    }

    for (auto& plant : plants) {
        int x = plant.x;
        int y = plant.y;
        int z = plant.z;
        m_pChunk->setBlock(x,y+1,z,getBiome(x, z).getPlant(m_random));
        m_pChunk->transparentChunk = true;
    }
    m_pChunk->buildedChunk = true;
}

const Biome& ClassicWorldGenerator::getBiome(int x, int z) const {
    int biomeValue = m_biomeMap.get(x, z);
    if (biomeValue >= 70) {
        return m_grassBiome;
    }
    else { //(biomeValue > 40 && biomeValue < 74) {
        return m_desertBiome;
    }
    //return m_grassBiome;
}