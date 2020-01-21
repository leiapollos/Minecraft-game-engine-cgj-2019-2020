#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "vector3.h"
#include <sstream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include "TextureAtlas.h"
#include "World/Block/BlockDatabase.h"

enum DataType{
        VERTICES = 0,
        TEXCOORDS = 1,
        NORMALS = 2,
        LIGHT = 3
};

typedef std::array<float,3> vec3;
typedef std::array<float,2> vec2;

class Mesh {
    private:
        bool inactive = false;
        GLuint vaoId;
        TextureAtlas* atlas;
        std::vector<Vector3> vertexData, normalData;
        std::vector<Vector2> texcoordData;
        std::vector<GLfloat> m_light;
        bool texcoordsLoaded, normalsLoaded, lightsLoaded;
        GLuint vboVertices, vboTexcoords, vboNormals, vboLights;
        std::vector<unsigned int> vertexIdx, texcoordIdx, normalIdx, lightIdx;
    public:
        std::vector<vec3> vertices, normals;
        std::vector<vec2> texcoords;
        
        Mesh();
        Mesh(const std::string& filename);
        Mesh(const std::vector<Vector3>& _verticesData,
           const std::vector<Vector2>& _texcoordData,
           const std::vector<Vector3>& _normalsData,
           const std::vector<unsigned int>&  _vIndices,
           const std::vector<unsigned int>&  _tIndices,
           const std::vector<unsigned int>&  _nIndices);
        virtual ~Mesh();
        void create();


        void print();
        void parseVertex(std::stringstream& sin);
        void parseTexcoord(std::stringstream& sin);
        void parseNormal(std::stringstream& sin);
        void parseFace(std::stringstream& sin);
        void parseLine(std::stringstream& sin);
        void loadMeshData(const std::string& filename);
        void processMeshData();
        void bind();
        int vertexDataCount();
        int textureDataCount();
        int normalDataCount();
        void addVertexData(const Vector3& v);
        void addLightData(float l);
        void addVertexIdx(unsigned int i);
        void addNormalIdx(unsigned int i);
        void addTextureIdx(unsigned int i);
        void addTextureData(const Vector2& vt);
        void addNormalData(const Vector3& vn);
        void resetMesh();
        void draw();
        void clear();
        void clearBufferData();
        void deleteBuffers();
};
#endif