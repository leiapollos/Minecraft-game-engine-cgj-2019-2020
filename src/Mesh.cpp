
#include "Mesh.h"
#include <SFML/Graphics.hpp>

Mesh::Mesh() {
    texcoordsLoaded = false;
    normalsLoaded=false;
    lightsLoaded=false;
    vboVertices = 0;
    vboTexcoords = 0;
    vboNormals = 0;
    vboLights = 0;
    vaoId = 0;
}

Mesh::Mesh(const std::string& filename) : Mesh() {
    loadMeshData(filename);     
    processMeshData();
    clear();
}

Mesh::Mesh(const std::vector<Vector3>& _verticesData,
           const std::vector<Vector2>& _texcoordData,
           const std::vector<Vector3>& _normalsData,
           const std::vector<unsigned int>&  _vIndices,
           const std::vector<unsigned int>&  _tIndices,
           const std::vector<unsigned int>&  _nIndices) : Mesh() {
    //loadMeshData(filename);
    vertexData = _verticesData;
    texcoordData = _texcoordData;
    normalData = _normalsData;
    vertexIdx = _vIndices;
    texcoordIdx = _tIndices;
    normalIdx = _nIndices;
    processMeshData();
    clear();
}

Mesh::~Mesh() {
    deleteBuffers();
    clear();
    clearBufferData();
}

void Mesh::create() {
    glGenVertexArrays(1,&vaoId);
    glBindVertexArray(vaoId);
    {
        glGenBuffers(1,&vboVertices);
        glBindBuffer(GL_ARRAY_BUFFER,vboVertices);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(VERTICES);
        glVertexAttribPointer(VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), (GLvoid *)0);

    }

    if(texcoordsLoaded) {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glGenBuffers(1, &vboTexcoords);
        glBindBuffer(GL_ARRAY_BUFFER, vboTexcoords);
        glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(texcoords[0]), texcoords.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(TEXCOORDS);
        glVertexAttribPointer(TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(texcoords[0]), (GLvoid *)0);
    }

    if(normalsLoaded) {
        glGenBuffers(1, &vboNormals);
        glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), normals.data(), GL_STATIC_DRAW);
        glEnableVertexAttribArray(NORMALS);
        glVertexAttribPointer(NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(normals[0]), (GLvoid *)0);
    }

    if(lightsLoaded) {
        glGenBuffers(1, &vboLights);
        glBindBuffer(GL_ARRAY_BUFFER, vboLights);
        glBufferData(GL_ARRAY_BUFFER, m_light.size() * sizeof(GLfloat), m_light.data(),
                     GL_STATIC_DRAW);
        glVertexAttribPointer(LIGHT, 1, GL_FLOAT, GL_FALSE, 0, (GLvoid *)0);
        glEnableVertexAttribArray(LIGHT);
    }
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

}

void Mesh::parseVertex(std::stringstream& sin) {
    Vector3 v = Vector3();
    sin >> v.x >> v.y >> v.z;
    vertexData.push_back(v);
}

void Mesh::parseTexcoord(std::stringstream& sin) {
    Vector2 v = Vector2();
    sin >> v.x >> v.y;
    texcoordData.push_back(v);
}

void Mesh::parseNormal(std::stringstream& sin) {
    Vector3 v = Vector3();
    sin >> v.x >> v.y >> v.z;
    normalData.push_back(v);
}

void Mesh::parseFace(std::stringstream& sin) {
    std::string token;
    if (normalData.empty() && texcoordData.empty()) {
        for (int i = 0; i < 3; i++) {
            sin >> token;
            vertexIdx.push_back(std::stoi(token));
        }
    } 
    else {
        for (int i = 0; i < 3; i++) {
            std::getline(sin, token, '/');
            if (token.size() > 0) vertexIdx.push_back(std::stoi(token));
            std::getline(sin, token, '/');
            if (token.size() > 0) texcoordIdx.push_back(std::stoi(token));
            std::getline(sin, token, ' ');
            if (token.size() > 0 && token[0] != '\r') normalIdx.push_back(std::stoi(token));
        }
    }
}

void Mesh::parseLine(std::stringstream& sin) {
    std::string s;
    sin >> s;
    if(s.compare("v") == 0)
        parseVertex(sin);
    else if(s.compare("vt") == 0)
        parseTexcoord(sin);
    else if(s.compare("vn") == 0)
        parseNormal(sin);
    else if(s.compare("f" ) == 0)
        parseFace(sin);
}

void Mesh::loadMeshData(const std::string& filename) {
    std::ifstream ifile(filename);
    while(ifile.good()) {
        std::string line;
        std::getline(ifile, line);
        std::stringstream sin(line);
        parseLine(sin);
    }
    texcoordsLoaded = (texcoordIdx.size() > 0);
    normalsLoaded = (normalIdx.size() > 0);
}

void Mesh::processMeshData(){
    texcoordsLoaded = (texcoordIdx.size() > 0);
    normalsLoaded = (normalIdx.size() > 0);
    lightsLoaded = (m_light.size() > 0);
    for(unsigned int i = 0; i < vertexIdx.size(); i++ ) {
        unsigned int vi = vertexIdx[i];
        Vector3 v = vertexData[vi - 1];
        vertices.push_back(v.data);
        if(texcoordsLoaded) {
            unsigned int ti = texcoordIdx[i];
            Vector2 t = texcoordData[ti - 1];
            texcoords.push_back(t.data);
        }
        if(normalsLoaded) {
            unsigned int ni = normalIdx[i];
            Vector3 n = normalData[ni - 1];
            normals.push_back(n.data);
        }
    }
}

void Mesh::print() {
    std::cout << "Vertices loaded: \n";
    int i, j;
    vec3 current;
    std::cout << vertices.size() << std::endl;
    for (i = 0; i < (int)(vertices.size()); i++) {
        current = vertices[i];
        for (j = 0; j < 3; j++) {
            std::cout << current[j] << "\t";
        }
        std::cout << "\n";
    }
}

void Mesh::bind(){
    glBindVertexArray(vaoId);
}

int Mesh::vertexDataCount() {
    return (int)vertexData.size();
}

int Mesh::textureDataCount() {
    return (int)texcoordData.size();
}

int Mesh::normalDataCount() {
    return (int)normalData.size();
}

void Mesh::addVertexData(const Vector3& v) {
    vertexData.push_back(v);
}

void Mesh::addNormalData(const Vector3& vn) {
    normalData.push_back(vn);
}

void Mesh::addLightData(float l) {
    m_light.push_back(l);
}

void Mesh::addTextureData(const Vector2& vt) {
    texcoordData.push_back(vt);
}
void Mesh::addVertexIdx(unsigned int i) {
    vertexIdx.push_back(i);
}

void Mesh::addNormalIdx(unsigned int i){
    normalIdx.push_back(i);
}

void Mesh::addTextureIdx(unsigned int i){
    texcoordIdx.push_back(i);
}

void Mesh::draw() {
    if(!vertices.empty() && vaoId != 0) {
        glBindVertexArray(vaoId);
        if (texcoordsLoaded){
            BlockDatabase::get().textureAtlas.bindTexture();
            //glBindTexture(GL_TEXTURE_2D, m_id);
        }
        //std::cout << vertices.size() << "\n";
        glDrawArrays(GL_TRIANGLES,0,(GLsizei)vertices.size());
        //BlockDatabase::get().textureAtlas.unbindTexture();
        //std::cout << "END" << "\n";
        //glDrawElements(GL_TRIANGLES, (GLsizei)vertices.size(), GL_UNSIGNED_INT, nullptr);
    }
}

void Mesh::resetMesh(){
    deleteBuffers();
    clear();
    clearBufferData();
    texcoordsLoaded = false;
    normalsLoaded=false;
    lightsLoaded=false;
    //glGenVertexArrays(1,&vaoId);
}

void Mesh::clear() {
    vertexData.clear();
    texcoordData.clear();
    normalData.clear();
    vertexIdx.clear();
    texcoordIdx.clear();
    normalIdx.clear();
    vertexData.shrink_to_fit();
    texcoordData.shrink_to_fit();
    normalData.shrink_to_fit();
    vertexIdx.shrink_to_fit();
    texcoordIdx.shrink_to_fit();
    normalIdx.shrink_to_fit();
}

void Mesh::clearBufferData() {
    m_light.clear();
    vertices.clear();
    normals.clear();
    texcoords.clear();
    normalData.clear();
    texcoordData.clear();
    m_light.shrink_to_fit();
    vertices.shrink_to_fit();
    normals.shrink_to_fit();
    texcoords.shrink_to_fit();
    normalData.shrink_to_fit();
    texcoordData.shrink_to_fit();
}

void Mesh::deleteBuffers() {
    glBindVertexArray(vaoId);
    glDisableVertexAttribArray(VERTICES);
    glDisableVertexAttribArray(TEXCOORDS);
    glDisableVertexAttribArray(NORMALS);
    glDisableVertexAttribArray(LIGHT);
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboVertices);
    glDeleteBuffers(1, &vboTexcoords);
    glDeleteBuffers(1, &vboNormals);
    glDeleteBuffers(1, &vboLights);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //exit(0);
}