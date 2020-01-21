#include "World.h"
World::World() {    
}
World::World(SceneGraph* n) {
    //BlockDatabase::get();
    typedef ResourcesManager RM;
    chunkManager = ChunkManager();
    waterShader = new ShaderProgram();
    solidShader = new ShaderProgram();
    transparentShader = new ShaderProgram();
    shadowMappingDepth = new ShaderProgram();
    debugShadowMappingDepth = new ShaderProgram();
    //shadow = new ShadowMapping();
    wGen = new ClassicWorldGenerator();
    //graph = n->getRoot();


    solidShader->compileShaderFromFile("../src/shaders/chunk.vert", ShaderType::VERTEX);
    solidShader->compileShaderFromFile("../src/shaders/chunk.frag", ShaderType::FRAGMENT);

    solidShader->bindAttribLocation(VERTICES,"in_Position");
    solidShader->bindAttribLocation(TEXCOORDS,"in_TexCoords");
    solidShader->bindAttribLocation(NORMALS,"in_Normal");
    solidShader->bindAttribLocation(LIGHT,"in_CardinalLight");
    solidShader->link();
    solidShader->addUniformBlock("SharedMatrices", n->getCamera()->UBO_BP);
    solidShader->detach();

    waterShader->compileShaderFromFile("../src/shaders/water.vert", ShaderType::VERTEX);
    waterShader->compileShaderFromFile("../src/shaders/water.frag", ShaderType::FRAGMENT);

    waterShader->bindAttribLocation(VERTICES,"in_Position");
    waterShader->bindAttribLocation(TEXCOORDS,"in_TexCoords");
    waterShader->bindAttribLocation(NORMALS,"in_Normal");
    waterShader->bindAttribLocation(LIGHT,"in_CardinalLight");
    waterShader->link();
    waterShader->addUniformBlock("SharedMatrices", n->getCamera()->UBO_BP);
	waterShader->detach();    
    
    transparentShader->compileShaderFromFile("../src/shaders/transparent.vert", ShaderType::VERTEX);
	transparentShader->compileShaderFromFile("../src/shaders/transparent.frag", ShaderType::FRAGMENT);

	transparentShader->bindAttribLocation(VERTICES, "in_Position");
	transparentShader->bindAttribLocation(TEXCOORDS, "in_TexCoords");
	transparentShader->bindAttribLocation(NORMALS, "in_Normal");
	transparentShader->bindAttribLocation(LIGHT, "in_CardinalLight");
	transparentShader->link();
	transparentShader->addUniformBlock("SharedMatrices", n->getCamera()->UBO_BP);
	transparentShader->detach();

    shadowMappingDepth->compileShaderFromFile("../src/shaders/shadowMappingDepth.vert", ShaderType::VERTEX);
    shadowMappingDepth->compileShaderFromFile("../src/shaders/shadowMappingDepth.frag", ShaderType::FRAGMENT);

	shadowMappingDepth->bindAttribLocation(VERTICES, "in_Position");
    shadowMappingDepth->bindAttribLocation(TEXCOORDS, "in_TexCoords");
    shadowMappingDepth->link();
    shadowMappingDepth->detach();
    
    debugShadowMappingDepth->compileShaderFromFile("../src/shaders/shadowMapping.vert", ShaderType::VERTEX);
    debugShadowMappingDepth->compileShaderFromFile("../src/shaders/shadowMapping.frag", ShaderType::FRAGMENT);

	debugShadowMappingDepth->bindAttribLocation(VERTICES, "in_Position");
	debugShadowMappingDepth->bindAttribLocation(TEXCOORDS, "in_TexCoords");
    debugShadowMappingDepth->link();
    debugShadowMappingDepth->detach();

    debugShadowMappingDepth->use();
    debugShadowMappingDepth->setUniform("depthMap", 0);

    for(int z = 0; z <= CHUNK_SIZE; z++)
        for(int y = 0; y <= CHUNK_SIZE; y++)
            for(int x = 0; x <= CHUNK_SIZE; x++) {
                RM::allVertices[x][y][z] = Vector3((float)x,(float)y,(float)z);
            }
    RM::allNormals.push_back(Vector3(0.0f,1.0f,0.0f));
    RM::allNormals.push_back(Vector3(0.0f,-1.0f,0.0f));
    RM::allNormals.push_back(Vector3(-1.0f,0.0f,0.0f));
    RM::allNormals.push_back(Vector3(1.0f,0.0f,0.0f));
    RM::allNormals.push_back(Vector3(0.0f,0.0f, -1.0f));
    RM::allNormals.push_back(Vector3(0.0f,0.0f, 1.0f));
    sceneGraph = n;
    const Vector3& player = n->getCamera()->getPosition();
    FPSCamera* c = (FPSCamera*) n->getCamera(); // lame will change later
    c->position = Vector3(player.x,(float)wGen->getMinimumSpawnHeight(),player.z);
    lastBuildPos = c->position;
    buildChunkAt((int)player.x/CHUNK_SIZE,(int)player.y/CHUNK_SIZE,(int)player.z/CHUNK_SIZE);
    //buildWorld((int)player.x/CHUNK_SIZE,(int)player.y/CHUNK_SIZE,(int)player.z/CHUNK_SIZE,RADIUS);
}

World::~World() {
    delete waterShader;
    delete solidShader;
}

void World::buildChunkMeshes() {
    ChunkMap& chunks = chunkManager.getChunks();
    //Chunk* c;
    ICamera* cam = sceneGraph->getCamera();
    const Vector3& player = cam->getPosition();
    
    //FPSCamera* fps = (FPSCamera*) sceneGraph->getCamera();
    int i = 0;
    for (auto &c : chunks) {
        Chunk* ck = c.second;
        if(ck != NULL && !ck->buildedMesh){
            if (distance(player, ck->pos) <= (RADIUS*CHUNK_SIZE)){
                ck->buildMesh(cam);
                i++;
                //break;
            }
            //if(c->waterChunk)
            //  waterChunks.push_back(c);
        }
        /*if (distance(player, c->pos) > ((RADIUS+1)*CHUNK_SIZE)) {
            toRemove.push_back(c);
        }*/
        if (i == RADIUS)
           break;
        
    }
    
    //std::cout << toRemove << "\n";

    
}

void World::update(float elapsed_sec) {
   deltaTime += (float)elapsed_sec;
   buildChunkMeshes();
}
bool World::buildChunkAt(int x, int y, int z) {
    if (!chunkManager.chunkExistsAt(x,y,z)) {
        Vector3 pos = Vector3((float)(x*CHUNK_SIZE),(float)(y*CHUNK_SIZE),(float)(z*CHUNK_SIZE));
        Chunk *a = new Chunk(pos, &chunkManager, wGen);
        chunkManager.setChunk(x*CHUNK_SIZE,y*CHUNK_SIZE,z*CHUNK_SIZE, a);
        return true;
    }
    return false;
}
void World::buildWorld(int x, int y, int z, int rad) {
    rad--;
    if (rad > 0) {
        
        if(buildChunkAt(x,y,z+1)) return;
        buildWorld(x,y,z+1,rad);
        //co_await;
        if(buildChunkAt(x,y,z-1)) return;
        buildWorld(x,y,z-1,rad);
        //co_await;
        if(buildChunkAt(x-1,y,z)) return;
        buildWorld(x-1,y,z,rad);
        //co_await;
        if(buildChunkAt(x+1,y,z)) return;
        buildWorld(x+1,y,z,rad);
        //co_await;
        if(buildChunkAt(x,y+1,z)) return;
        buildWorld(x,y+1,z,rad);
        //co_await;
        if(buildChunkAt(x,y-1,z)) return;
        buildWorld(x,y-1,z,rad);
    }
}

//blend
float blend(float x, float y, float factor)
{
	return x + ((y - x) * factor);
}

void World::computeLight(float time) {
    time = fmodf(time,300.0f);
	/*if (time > 300) {
		time = 0;
	}*/
    //std::cout << time << "\n";
	//Ambient light
	//0 = 6am
	//12000 = 6pm
	if (time < 37.5f)  //6am - 9am sun gets brighter
	{
		lighting = blend(0.6f, 1.0f, time / 37.5f);
	}
	if (time > 37.5f && time < 112.5f)  //9am - 3pm sun is brightest
	{
		lighting = 1.0f;
	}
	if (time > 112.5f && time < 150.0f)  //3pm - 6pm sun gets dimmer
	{
		lighting = blend(1.0f, 0.6f, (float)(time - 112.5f) / 37.5f);
	}
	if (time > 150.0f && time < 187.5f)  //6pm - 9pm sun light fades
	{
		lighting = blend(0.6f, 0.2f, (float)(time - 150.0f) / 37.5f);
	}
	if (time > 187.5f && time < 262.5f) //9pm - 3am is night
	{
		lighting = 0.2f;
	}
	if (time > 262.5f && time < 300)
	{
		lighting = blend(0.2f, 0.6f, (float)(time - 262.5) / 37.5f);
	}
}

void World::draw(float elapsed_sec) {
    ChunkMap& chunks = chunkManager.getChunks();
    ICamera* cam = sceneGraph->getCamera();
    const Vector3& player = cam->getPosition();

    //// SHADOW

    /*shadow->renderDepth(shadowMappingDepth, player);
	for (auto it : chunks) {
		Chunk* c = it.second;
		if (c != NULL)
			if (distance(player, c->pos) <= RADIUS * CHUNK_SIZE)
				c->draw(shadowMappingDepth, cam);
	}
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// reset viewport
	glViewport(0, 0, 1280, 720);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    shadow->quad(debugShadowMappingDepth);

	glViewport(0, 0, 1280, 720);*/
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //// SHADOW


	//skyManager->timeUpdate(deltaTime);
    
    //Solid Mesh Rendering
    /**/
    glDisable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    solidShader->use();
	computeLight(deltaTime);
	solidShader->setUniform("lighting", lighting);
    //solidShader->setUniform("lightSpaceMatrix", shadow->lightSpaceMatrix.data);
	//shadow->bindDepthMap();

    //Check if under water and if yes then draw scene bluish
    int x = (int)player.data[0];
    int y = (int)player.data[1];
    int z = (int)player.data[2]; 
    Chunk* current = chunkManager.getChunkGlobal(x,y,z);
    if (current != NULL) {
        //std::cout << "\n" << x << " " << y << " "<< z << "\n";
        //std::cout << "------------------------------\n";

        BlockId cb = current->getBlock(x%CHUNK_SIZE, y%CHUNK_SIZE, z%CHUNK_SIZE);
        if (cb == current->getBlockId(BlockId::WATER)) {
            solidShader->setUniform("InWater", 0.75f, 0.75f, 1.45f, 1.0f);
        }
        else {
            solidShader->setUniform("InWater", 1.0f, 1.0f, 1.0f, 1.0f);
        }
    }else solidShader->setUniform("InWater", 1.0f, 1.0f, 1.0f, 1.0f);
    

    for (auto &c : chunks){
        Chunk* ck = c.second;
        if (ck != NULL)
            if (distance(player, ck->pos) <= RADIUS*CHUNK_SIZE)
                ck->draw(solidShader, cam);
    }

    // Water Rendering
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    waterShader->use();
	waterShader->setUniform("globalTime", deltaTime); 
	waterShader->setUniform("lighting", lighting);

   // std::map<float, GameObject*> transparentChunkSorted;
    for (auto &c : chunks){
        Chunk* ck = c.second;
        if (ck != NULL && ck->waterChunk) {
            if (distance(player, ck->pos) <= RADIUS*CHUNK_SIZE)
                //if (cam->getFrustum().isBoxInFrustum(ck->chunkW.m_aabb))
                    ck->chunkW.draw(waterShader, cam);
        }
//         if (ck != NULL && ck->transparentChunk) { //Make map of transparent chunks
//             if (distance(player, ck->pos) <= RADIUS * CHUNK_SIZE)
// 				for (auto& t : ck->chunkT) {
// 					float d = distance(player, t.first);
//                     GameObject* g = t.second;
// 					transparentChunkSorted.emplace(d, g);
// 				}
//         }
    }
           
    
    
//     for (auto& c : transparentChunkSorted) {
//         if(c.second!=NULL)
//             (*c.second).draw(transparentShader, cam);
//     }
    /**/

    glEnable(GL_BLEND);
    glEnable(GL_CULL_FACE);
    //glDisable(GL_CULL_FACE);
    m_Sky.Render(*cam, deltaTime);
    m_clouds.Render(*cam, elapsed_sec, lighting);


    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDisable(GL_CULL_FACE);
    glEnable(GL_CULL_FACE);
    transparentShader->use();
    transparentShader->setUniform("globalTime", deltaTime);
    transparentShader->setUniform("lighting", lighting);
    for (auto& c : chunks) {
        Chunk* ck = c.second;
        if (ck != NULL && ck->transparentChunk) {
            if (distance(player, ck->pos) <= RADIUS * CHUNK_SIZE){
                //if (cam->getFrustum().isBoxInFrustum(ck->chunkW.m_aabb))
                ck->chunkT.draw(transparentShader, cam);
            }
        }
    }
    
    for(auto &c : chunks) {
        Chunk* ck = c.second;
        if (distance(player, ck->pos) > RADIUS*CHUNK_SIZE && ck->buildedMesh)
            ck->resetMeshes();
    }



    /*toRemove.clear();*/
     /*std::vector<Chunk*>::iterator pend; 
    }
    for (std::vector<Chunk*>::iterator p = toRemove.begin(); p != pend; ++p) 
        if(p>buildedMesh) {
            
            delete p;
        }
    }
    toRemove.clear();*/
}