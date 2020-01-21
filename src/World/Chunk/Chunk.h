#ifndef CHUNK_H
#define CHUNK_H
#include "../../vector3.h"
#include "../../Mesh.h"
#include "../../GameObject.h"
#include "IChunk.h"
#include "../../Constants.h"
#include "../Block/BlockDatabase.h"
#include "../Block/BlockId.h"
#include "ChunkMeshBuilder.h"
#include "../WorldConstants.h"
#include "ChunkManager.h"
#include "../../ICamera.h"
#include "../Generation/Terrain/TerrainGenerator.h"
class World;
class Chunk : IChunk {
	public:
		GameObject chunk;
		GameObject chunkW;
		GameObject chunkT;
		ChunkManager* chunkManager;
		ChunkMeshBuilder chunkBuilder;
		Vector3 pos;
		bool buildedMesh;
		bool buildedChunk;
		BlockId chunkData[CHUNK_VOLUME];
		bool waterChunk;
		bool transparentChunk;
		bool treesBuilded;

		Chunk() = default;
		Chunk(const Vector3& position, ChunkManager* cm, TerrainGenerator* wGen);
		virtual ~Chunk();
		void buildChunk();
		void buildMesh(ICamera* cam);
		void buildTree(int x, int y, int z);
		void draw(ShaderProgram* s, ICamera* cam);
		bool checkNeighbourBlocksForId(int x, int y, int z, BlockId id);
		BlockId getBlock(int x, int y, int z);
		BlockId getBlockId(BlockId id);
		void setBlock(const Vector3& pos, const BlockId block);
		void setBlock(int x,int y, int z, BlockId block);
		int convertBlockIndexToLocal(int i);
		Chunk* getChunkOutOfBounds(int x, int y, int z);
		void resetMeshes();
	private:
		TerrainGenerator* m_pWorldGen;

};
#endif