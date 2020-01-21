#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <unordered_map>
#include <unordered_set>
#include "../../vector3.h"
#include "../WorldConstants.h"
#include "../Block/BlockId.h"
#include "../../Maths/VectorXYZ.h"
#include <iostream>
//class Chunk;
//class World;
class Chunk;

using ChunkMap = std::unordered_map<sf::Vector3i, Chunk*>;
class ChunkManager {
    public:
        int m_pChunksBuilded;
        ChunkManager();

        Chunk* getChunkGlobal(int x, int y, int z);
        Chunk* getChunk(int x, int y, int z);
        void setChunk(int x, int y, int z, Chunk* c);
        ChunkMap& getChunks();

        bool makeMesh(int x, int y, int z);

        bool chunkLoadedAt(int x, int y, int z) const;
        bool chunkExistsAt(int x, int y, int z) const;

        void loadChunk(int x, int y, int z);
        void unloadChunk(int x, int y, int z);
        void deleteChunks();
    private:
        //std::unique_ptr<TerrainGenerator> m_terrainGenerator;
        ChunkMap m_chunks;
        int m_pTotalChunks;
        
};

#endif // CHUNKMANAGER_H