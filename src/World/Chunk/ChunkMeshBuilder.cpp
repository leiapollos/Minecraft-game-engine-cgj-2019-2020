#include "ChunkMeshBuilder.h"
ChunkMeshBuilder::ChunkMeshBuilder(IChunk* chunk) : m_pChunk(chunk) {

}


void ChunkMeshBuilder::buildMesh(Mesh* m, int x, int y , int z, bool water = false, bool transparent = false) {
	//TextAttrib t();
	buildBlockFaces(m, x, y, z,BlockDatabase::get().getData(m_pChunk->getBlock(x,y,z)).getBlockData().ta, water, transparent);
}

bool ChunkMeshBuilder::hasSolidNeighbour(int x, int y, int z,
										 int adjx, int adjy, int adjz) {
	BlockId adjId = m_pChunk->getBlock(adjx+x,adjy+y,adjz+z);
	if(adjId != BlockId::AIR && adjId != BlockId::LEAVES) {
		BlockId bId = m_pChunk->getBlock(x,y,z);
		bool isOpaque = BlockDatabase::get().getData(adjId).getBlockData().isOpaque;
		return (isOpaque || bId==adjId);
	}
	return false;
}

void ChunkMeshBuilder::buildBlockFaces(Mesh* m, int x, int y, int z, const TextAttrib& ta, bool water, bool transparent) {
	int adjPos[][3] = { {0,-1,0} ,  {0,1,0} ,  {-1,0,0} ,  {1,0,0},  {0,0,1}, {0,0,-1} };
	//std::cout << "------------\n";
	BlockId b = m_pChunk->getBlock(x,y,z);
	BlockMeshType mType = BlockDatabase::get().getData(m_pChunk->getBlock(x,y,z)).getBlockData().meshType;
	//if (b == NULL)
	//	throw std::runtime_error("WTF\n");
	if (b == BlockId::AIR)
		return;
	if ((!water && b == BlockId::WATER))
		return;
	if (water && b != BlockId::WATER)
		return;
	if (water && mType == BlockMeshType::Cube) {
		for (int cs = BOTTOM; cs <=BACK; cs++) {
			if(!hasSolidNeighbour(x,y,z,adjPos[cs][0],adjPos[cs][1],adjPos[cs][2]) && cs == TOP)
				createQuad(m,static_cast<Cubeside>(TOP),x,y,z, ta);
		}
	}	
	if ((!transparent && b == BlockId::LEAVES))
		return;
	if (transparent && (b != BlockId::LEAVES && mType != BlockMeshType::X))
		return;
	if (transparent) {
		if (mType == BlockMeshType::X) {
			createX1(m,x,y,z,ta);
			createX2(m,x,y,z,ta);

			
		}
		else {
			for (int cs = BOTTOM; cs <= BACK; cs++) {
				if (!hasSolidNeighbour(x, y, z, adjPos[cs][0], adjPos[cs][1], adjPos[cs][2]))
					createQuad(m, static_cast<Cubeside>(cs), x, y, z, ta);
			}
		}
	}
	else {
		if (mType == BlockMeshType::Cube) {
			for (int cs = BOTTOM; cs <=BACK; cs++) {
				if(!hasSolidNeighbour(x,y,z,adjPos[cs][0],adjPos[cs][1],adjPos[cs][2]))
					createQuad(m,static_cast<Cubeside>(cs),x,y,z, ta);
			}
		}
	}
}

void ChunkMeshBuilder::createFace(const Vector3& p0,
					const Vector3& p1,
					const Vector3& p2,
					const Vector3& p3,
					const std::vector<Vector2>& t,
					const Vector3& n,
					float l,
					Mesh* m) {
	int trioffset = m->vertexDataCount();
	int normOffset = m->normalDataCount();
	m->addVertexData(p0); m->addVertexData(p1); m->addVertexData(p2); m->addVertexData(p3);
	m->addNormalData(n);

	m->addTextureData(t[0]);
	m->addTextureData(t[1]);
	m->addTextureData(t[2]);
	m->addTextureData(t[3]);
	
	// Vertex Indices
	m->addVertexIdx(1 + trioffset); m->addVertexIdx(4 + trioffset); m->addVertexIdx(2 + trioffset);
	m->addVertexIdx(3 + trioffset); m->addVertexIdx(2 + trioffset); m->addVertexIdx(4 + trioffset);

	// Texture Indices
	m->addTextureIdx(trioffset + 1); m->addTextureIdx(trioffset + 2); m->addTextureIdx(trioffset + 3);
	m->addTextureIdx(trioffset + 4); m->addTextureIdx(trioffset + 3); m->addTextureIdx(trioffset + 2);
	// Normal Indices
	m->addNormalIdx(normOffset+1);m->addNormalIdx(normOffset+1);m->addNormalIdx(normOffset+1);
	m->addNormalIdx(normOffset+1);m->addNormalIdx(normOffset+1);m->addNormalIdx(normOffset+1);
	m->addLightData(l);m->addLightData(l);m->addLightData(l);
	m->addLightData(l);m->addLightData(l);m->addLightData(l);
}

void ChunkMeshBuilder::createTop(Mesh* m, int x, int y, int z, const TextAttrib& ta) {
	typedef ResourcesManager RM;
	/*float x = (float)_x;
	float y = (float)_y;
	float z = (float)_z;
	Vector3 p0 = Vector3(x,y+1,z);
	Vector3 p1 = Vector3(x+1,y+1,z);
	Vector3 p2 = Vector3(x+1,y+1,z+1);
	Vector3 p3 = Vector3(x,y+1,z+1);
	Vector3 n = Vector3(0,1,0);*/
	//BlockDatabase::get();
	createFace(RM::allVertices[x][y+1][z],
		RM::allVertices[x+1][y+1][z],
		RM::allVertices[x+1][y+1][z+1],
		RM::allVertices[x][y+1][z+1],
		ta.getTextDataTop(),
		RM::allNormals[0],
		1.0f,
		m);

}

void ChunkMeshBuilder::createBot(Mesh* m, int x, int y, int z, const TextAttrib& ta) {
	typedef ResourcesManager RM;
	/*float x = (float)_x;
	float y = (float)_y;
	float z = (float)_z;
	Vector3 p0 = Vector3(x,y,z+1);
	Vector3 p1 = Vector3(x+1,y,z+1);
	Vector3 p2 = Vector3(x+1,y,z);
	Vector3 p3 = Vector3(x,y,z);
	Vector3 n = Vector3(0,-1,0);*/
	createFace(RM::allVertices[x][y][z+1],
		RM::allVertices[x+1][y][z+1],
		RM::allVertices[x+1][y][z],
		RM::allVertices[x][y][z],
		ta.getTextDataBottom(),
		RM::allNormals[1],
		0.4f,
		m);
}

void ChunkMeshBuilder::createLeft(Mesh* m, int x, int y, int z, const TextAttrib& ta) {
	//p7,p4,p0,p3
	typedef ResourcesManager RM;
	/*float x = (float)_x;
	float y = (float)_y;
	float z = (float)_z;
	Vector3 p0 = Vector3(x,y+1,z);
	Vector3 p1 = Vector3(x,y+1,z+1);
	Vector3 p2 = Vector3(x,y,z+1);
	Vector3 p3 = Vector3(x,y,z);
	Vector3 n = Vector3(-1,0,0);*/
	createFace(RM::allVertices[x][y+1][z]
		,RM::allVertices[x][y+1][z+1]
		,RM::allVertices[x][y][z+1]
		,RM::allVertices[x][y][z]
		,ta.getTextDataLeft(),
		RM::allNormals[2],
		0.8f,
		m);
}

void ChunkMeshBuilder::createX1(Mesh* m, int x, int y, int z, const TextAttrib& ta) {
	//p7,p4,p0,p3
	typedef ResourcesManager RM;
	/*float x = (float)_x;
	float y = (float)_y;
	float z = (float)_z;
	Vector3 p0 = Vector3(x,y+1,z);
	Vector3 p1 = Vector3(x,y+1,z+1);
	Vector3 p2 = Vector3(x,y,z+1);
	Vector3 p3 = Vector3(x,y,z);
	Vector3 n = Vector3(-1,0,0);*/
	createFace(RM::allVertices[x][y+1][z]
		,RM::allVertices[x+1][y+1][z+1]
		,RM::allVertices[x+1][y][z+1]
		,RM::allVertices[x][y][z]
		,ta.getTextDataLeft(),
		RM::allNormals[2],
		0.8f,
		m);

	createFace(RM::allVertices[x+1][y+1][z+1]
		,RM::allVertices[x][y+1][z]
		,RM::allVertices[x][y][z]
		,RM::allVertices[x+1][y][z+1]
		,ta.getTextDataLeft(),
		RM::allNormals[2],
		0.8f,
		m);


	

}

void ChunkMeshBuilder::createX2(Mesh* m, int x, int y, int z, const TextAttrib& ta) {
	//p7,p4,p0,p3
	typedef ResourcesManager RM;
	/*float x = (float)_x;
	float y = (float)_y;
	float z = (float)_z;
	Vector3 p0 = Vector3(x,y+1,z);
	Vector3 p1 = Vector3(x,y+1,z+1);
	Vector3 p2 = Vector3(x,y,z+1);
	Vector3 p3 = Vector3(x,y,z);
	Vector3 n = Vector3(-1,0,0);*/
	createFace(RM::allVertices[x][y+1][z+1]
		,RM::allVertices[x+1][y+1][z]
		,RM::allVertices[x+1][y][z]
		,RM::allVertices[x][y][z+1]
		,ta.getTextDataLeft(),
		RM::allNormals[3],
		0.8f,
		m);
	createFace(RM::allVertices[x+1][y+1][z]
		,RM::allVertices[x][y+1][z+1]
		,RM::allVertices[x][y][z+1]
		,RM::allVertices[x+1][y][z]
		,ta.getTextDataLeft(),
		RM::allNormals[3],
		0.8f,
		m);

}

void ChunkMeshBuilder::createRight(Mesh* m, int x, int y, int z, const TextAttrib& ta) {
	//p5,p6,p2,p1
	typedef ResourcesManager RM;
	/*float x = (float)_x;
	float y = (float)_y;
	float z = (float)_z;
	Vector3 p0 = Vector3(x+1,y+1,z+1);
	Vector3 p1 = Vector3(x+1,y+1,z);
	Vector3 p2 = Vector3(x+1,y,z);
	Vector3 p3 = Vector3(x+1,y,z+1);
	Vector3 n = Vector3(1,0,0);*/
	createFace(RM::allVertices[x+1][y+1][z+1],
		RM::allVertices[x+1][y+1][z],
		RM::allVertices[x+1][y][z],
		RM::allVertices[x+1][y][z+1],
		ta.getTextDataRight(),
		RM::allNormals[3],
		0.8f,
		m);
}

void ChunkMeshBuilder::createFront(Mesh* m, int x, int y, int z, const TextAttrib& ta) {
	//p4,p5,p1,p0
	typedef ResourcesManager RM;
	/*float x = (float)_x;
	float y = (float)_y;
	float z = (float)_z;
	Vector3 p0 = Vector3(x,y+1,z+1);
	Vector3 p1 = Vector3(x+1,y+1,z+1);
	Vector3 p2 = Vector3(x+1,y,z+1);
	Vector3 p3 = Vector3(x,y,z+1);
	Vector3 n = Vector3(0,0,1);*/
	createFace(RM::allVertices[x][y+1][z+1],
		RM::allVertices[x+1][y+1][z+1],
		RM::allVertices[x+1][y][z+1],
		RM::allVertices[x][y][z+1],
		ta.getTextDataFront(),
		RM::allNormals[4],
		0.6f,
		m);
}

void ChunkMeshBuilder::createBack(Mesh* m, int x, int y, int z, const TextAttrib& ta) {
	//p6,p7,p3,p2
	typedef ResourcesManager RM;
	/*float x = (float)_x;
	float y = (float)_y;
	float z = (float)_z;
	Vector3 p0 = Vector3(x+1,y+1,z);
	Vector3 p1 = Vector3(x,y+1,z);
	Vector3 p2 = Vector3(x,y,z);
	Vector3 p3 = Vector3(x+1,y,z);
	Vector3 n = Vector3(0,0,-1);*/
	createFace(RM::allVertices[x+1][y+1][z],
		RM::allVertices[x][y+1][z],
		RM::allVertices[x][y][z],
		RM::allVertices[x+1][y][z],
		ta.getTextDataBack(),
		RM::allNormals[5],
		0.6f,
		m);
}

void ChunkMeshBuilder::createQuad(Mesh* m, Cubeside side, int x, int y , int z, const TextAttrib& ta) {
	//4444typedef ResourcesManager RM;
	/*float x = position.x;
	float y = position.y;
	float z = position.z;

	Vector3 p0 = Vector3(x,y,z+1);
	Vector3 p1 = Vector3(x+1,y,z+1);
	Vector3 p2 = Vector3(x+1,y,z);
	Vector3 p3 = Vector3(x,y,z);
	Vector3 p4 = Vector3(x,y+1,z+1);
	Vector3 p5 = Vector3(x+1,y+1,z+1);
	Vector3 p6 = Vector3(x+1,y+1,z);
	Vector3 p7 = Vector3(x,y+1,z);*/

	switch (side) {
		case BOTTOM:
			createBot(m,x,y,z, ta);
			//createFace(p0,p1,p2,p3,ta.getTextDataBottom(),Vector3(0,-1,0), m);
			break;

		case TOP:
			createTop(m,x,y,z, ta);
			//createFace(p7,p6,p5,p4,ta.getTextDataTop(),Vector3(0,1,0), m);
			break;

		case LEFT:
			createLeft(m,x,y,z, ta);
			//createFace(p7,p4,p0,p3,ta.getTextDataLeft(),Vector3(-1,0,0), m);
			break;

		case RIGHT:
			createRight(m,x,y,z, ta);
			//createFace(p5,p6,p2,p1,ta.getTextDataRight(),Vector3(1,0,0), m);
			break;

		case FRONT:
			createFront(m,x,y,z, ta);
			//createFace(p4,p5,p1,p0,ta.getTextDataFront(),Vector3(0,0,1), m);
			break;
		
		case BACK:
			createBack(m,x,y,z, ta);
			//createFace(p6,p7,p3,p2,ta.getTextDataBack(),Vector3(0,0,-1), m);
			break;

		default:
			break;
	}
}