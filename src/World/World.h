#ifndef WORLD_H
#define WORLD_H
#include "Chunk/ChunkManager.h"
#include "../SceneGraph.h"
#include "../SceneNode.h"
#include "Chunk/Chunk.h"
#include "../ShaderProgram.h"
#include <iostream>
#include "../FPSCamera.h"
#include "../ResourcesManager.h"
#include "WorldConstants.h"
#include <math.h>
#include "../Maths/VectorXYZ.h"
#include "../ShadowMapping.h"
#include "Generation/Terrain/ClassicWorldGenerator.h"
#include "../Sky/Cloud.h"
#include "../ScreenShot.h"
#include "../Sky/Sky.h"
//class Chunk;
class World {
	public:

		ShaderProgram* waterShader;
		ShaderProgram* solidShader;
		ShaderProgram* shadowMappingDepth;
		ShaderProgram* debugShadowMappingDepth;
		ShaderProgram* transparentShader;
		ShadowMapping* shadow;
		SceneGraph* sceneGraph;
		SceneNode* graph;
		bool coroutineEnd = false;
		float deltaTime=0;
		ChunkManager chunkManager;
		//Clouds m_clouds;
		ClassicWorldGenerator* wGen;
		Vector3 lastBuildPos;
		float lighting=0;
		World(SceneGraph* n);
		World();
		~World();
		void buildChunkMeshes();
		bool buildChunkAt(int x, int y, int z);
		void buildWorld(int x, int y, int z, int rad);
		void draw(float deltaTime);
		void computeLight(float time);
		void update(float deltaTime);
	private:
		Clouds m_clouds;
		Sky m_Sky;
};
#endif