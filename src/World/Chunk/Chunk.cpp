#include "Chunk.h"

Chunk::Chunk(const Vector3& position, ChunkManager* cm, TerrainGenerator* wGen) 
						: chunk(position), 
						  chunkW(position),
						  chunkT(position),
						  chunkBuilder(this),
						  pos(position) {
	m_pWorldGen = wGen;
	waterChunk = false;
	transparentChunk = false;
	chunkManager = cm;
	buildedMesh = false;
	buildedChunk = false;
	treesBuilded = false;
	for (int x = 0; x < CHUNK_SIZE; ++x){
		for (int y = 0; y < CHUNK_SIZE; ++y){
			for (int z = 0; z < CHUNK_SIZE; ++z){
				setBlock(x,y,z, BlockId::AIR);
			}
		}
	}
	m_pWorldGen->generateTerrainFor(*this);
}


Chunk::~Chunk() {}


BlockId Chunk::getBlockId(BlockId id) {
	return BlockDatabase::get().getData(id).getBlockData().id;
}

void Chunk::buildMesh(ICamera* cam) {
	if (!buildedMesh) { //&& cam->getFrustum().isBoxInFrustum(chunk.m_aabb)) {
		for (int z = 0; z < CHUNK_SIZE; z++)
				for (int y = 0; y < CHUNK_SIZE; y++)
					for (int x = 0; x < CHUNK_SIZE; x++) {
						chunkBuilder.buildMesh(&chunk.mesh, x, y, z, false, false);
						if(waterChunk)
							chunkBuilder.buildMesh(&chunkW.mesh, x, y, z, waterChunk, false);
						if (transparentChunk) {
							chunkBuilder.buildMesh(&chunkT.mesh, x, y, z, false, transparentChunk);
						}
					}
		
		chunk.mesh.processMeshData();
		chunk.mesh.clear();
		chunk.mesh.create();
		if (waterChunk) {
			chunkW.mesh.processMeshData();
			chunkW.mesh.clear();
			chunkW.mesh.create();
		}
		if (transparentChunk) {
			chunkT.mesh.processMeshData();
			chunkT.mesh.clear();
			chunkT.mesh.create();
		}
		buildedMesh = true;
		chunkManager->m_pChunksBuilded++;
	}
}

void Chunk::draw(ShaderProgram* s, ICamera* cam) {
	//if(cam->getFrustum().isBoxInFrustum(chunk.m_aabb))
		chunk.draw(s, cam);
}

int Chunk::convertBlockIndexToLocal(int i) {
	if(i <= -1) 
		i = CHUNK_SIZE+i; 
	else if(i >= CHUNK_SIZE) 
		i = i-CHUNK_SIZE;
	return i;
}

Chunk* Chunk::getChunkOutOfBounds(int x, int y, int z) {
	int newX = (int)pos.x, newY = (int)pos.y, newZ = (int)pos.z;
	newX += (int) floor((float)x/CHUNK_SIZE) * CHUNK_SIZE;
	newY += (int) floor((float)y/CHUNK_SIZE) * CHUNK_SIZE;
	newZ += (int) floor((float)z/CHUNK_SIZE) * CHUNK_SIZE;
	Chunk* _chunk = chunkManager->getChunk(newX,newY,newZ);
	if (_chunk != NULL) {
		return _chunk;
	}
	_chunk = new Chunk(Vector3((float)newX,(float)newY,(float)newZ),chunkManager, m_pWorldGen);
	chunkManager->setChunk(newX,newY,newZ, _chunk);
	return _chunk;
}

BlockId Chunk::getBlock(int x, int y, int z) {
	if (x < 0 || x>= CHUNK_SIZE || y < 0 || y>= CHUNK_SIZE || z < 0 || z>= CHUNK_SIZE) {
		int _x = convertBlockIndexToLocal(x);
		int _y = convertBlockIndexToLocal(y);
		int _z = convertBlockIndexToLocal(z);
		return getChunkOutOfBounds(x,y,z)->getBlock(_x,_y,_z);
	}
	return chunkData[x*CHUNK_SIZE*CHUNK_SIZE + y*CHUNK_SIZE + z];
}

void Chunk::setBlock(const Vector3& pos, BlockId block) {
	int x = (int) pos.x;
	int y = (int) pos.y;
	int z = (int) pos.z;
	setBlock(x,y,z, block);
}

void Chunk::setBlock(int x,int y, int z, BlockId block) {
	if (x < 0 || x>= CHUNK_SIZE || y < 0 || y>= CHUNK_SIZE || z < 0 || z>= CHUNK_SIZE) {
		int newX = (int)pos.x, newY = (int)pos.y, newZ = (int)pos.z;
		newX += (int) (floor((float)(x/CHUNK_SIZE)) * CHUNK_SIZE);
		newY += (int) (floor((float)(y/CHUNK_SIZE)) * CHUNK_SIZE);
		newZ += (int) (floor((float)(z/CHUNK_SIZE)) * CHUNK_SIZE);
		Chunk* c = chunkManager->getChunk(newX,newY,newZ);
		int _x = convertBlockIndexToLocal(x);
		int _y = convertBlockIndexToLocal(y);
		int _z = convertBlockIndexToLocal(z);
		if (c != NULL) {
			if(!c->buildedMesh)
				c->setBlock(_x,_y,_z, block);
			else{
				c->setBlock(_x,_y,_z, block);
				c->resetMeshes();
				c->buildMesh(NULL);
			}
		}
		else {
			/*std::cout << "---------------------\n";
			std::cout << "Current Chunk: " <<pos;
			std::cout << "New Chunk: "<<Vector3(newX,newY,newZ);
			std::cout << x << " " << y << " " <<z<<"\n";
			std::cout << _x << " " << _y << " " <<_z<<"\n";
			std::cout << "---------------------\n";;*/
			c = new Chunk(Vector3((float)newX,(float)newY,(float)newZ),chunkManager, m_pWorldGen);
			chunkManager->setChunk(newX,newY,newZ, c);
			c->setBlock(_x,_y,_z, block);
		}
		return;
	}
	else {
		chunkData[x*CHUNK_SIZE*CHUNK_SIZE + y*CHUNK_SIZE + z] = block;
	}
}

void Chunk::resetMeshes() {
	chunk.resetMesh();
	chunkW.resetMesh();
	chunkT.resetMesh();
	buildedMesh = false;
	treesBuilded = false;
}