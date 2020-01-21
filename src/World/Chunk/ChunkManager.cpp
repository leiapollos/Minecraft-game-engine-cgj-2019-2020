#include "ChunkManager.h"

ChunkManager::ChunkManager() 
                        : m_pChunksBuilded(0), 
                          m_pTotalChunks(0) {}

Chunk* ChunkManager::getChunkGlobal(int x, int y, int z) {
    int cx = (int)floor(x/CHUNK_SIZE) * CHUNK_SIZE;
    int cy = (int)floor(y/CHUNK_SIZE) * CHUNK_SIZE;
    int cz = (int)floor(z/CHUNK_SIZE) * CHUNK_SIZE;
	if (!chunkExistsAt(cx, cy, cz)) {
		return NULL;
	}

	return m_chunks.at({cx, cy, cz});
}

Chunk* ChunkManager::getChunk(int x, int y, int z) {
    if (!chunkExistsAt(x, y, z)) {
        return NULL;
    }
    return m_chunks.at({x, y , z});
}

void ChunkManager::setChunk(int x, int y, int z, Chunk* c) {
    m_pTotalChunks++;
    //std::cout << m_pTotalChunks << "\n";
    sf::Vector3i key{x,y,z};
    m_chunks.emplace(key, std::move(c));
}

ChunkMap& ChunkManager::getChunks(){
    return m_chunks;
}

bool ChunkManager::makeMesh(int x, int y, int z) {
    return false;
}

bool ChunkManager::chunkLoadedAt(int x, int y, int z) const {
    return false;
}


bool ChunkManager::chunkExistsAt(int x, int y, int z) const {
    return m_chunks.find({x, y, z}) != m_chunks.end();
}

void ChunkManager::loadChunk(int x, int y, int z) {}

void ChunkManager::unloadChunk(int x, int y, int z) {
     if (chunkExistsAt(x, y, z)){
        m_chunks.erase({x,y,z});
        m_pTotalChunks--;
        m_pChunksBuilded--;
    }
     //return nullptr; //TODO FIX THIS LINE
}

void ChunkManager::deleteChunks() {
    /*for (std::pair<Vector3, Chunk*> it : m_chunks) {
        delete it.second;
    }
    m_chunks.clear();*/
    /*std::unordered_map<Vector3, Chunk*>::iterator it = m_chunks.begin();
    Chunk* c;
    while (it != m_chunks.end()) {
        c = it->second;
        if (c != NULL)
            delete c;
        m_chunks.erase(it);
        it = m_chunks.begin();
    }*/
}