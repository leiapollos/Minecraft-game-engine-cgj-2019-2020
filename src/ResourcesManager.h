#ifndef RESOURCESMANAGER_H
#define RESOURCESMANAGER_H
#include <SFML/Graphics.hpp>
#include "vector3.h"
#include "TextureAtlas.h"
class Chunk;
class ResourcesManager {
	public:
		static std::vector<Vector3> allNormals;
		static Vector3 allVertices[17][17][17];
		ResourcesManager();
		~ResourcesManager();
		
};
#endif