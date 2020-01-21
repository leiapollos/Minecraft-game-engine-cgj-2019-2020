#ifndef CHUNKMESHBUILDER_H
#define CHUNKMESHBUILDER_H
#include "../Block/BlockDatabase.h"
#include "../Block/BlockId.h"
#include "../../Mesh.h"
#include "IChunk.h"
#include "../../ResourcesManager.h"
class ChunkMeshBuilder {
  public:
    enum Cubeside {
        BOTTOM, TOP, LEFT, RIGHT, FRONT, BACK
    };
    ChunkMeshBuilder() = default;
    ChunkMeshBuilder(IChunk* chunk);

    void buildMesh(Mesh*, int, int, int, bool, bool);

  private:
    IChunk* m_pChunk;
    void createTop(Mesh*, int ,int ,int, const TextAttrib&);
    void createBot(Mesh*, int ,int ,int, const TextAttrib&);
    void createLeft(Mesh*, int ,int ,int, const TextAttrib&);
    void createRight(Mesh*, int ,int ,int, const TextAttrib&);
    void createFront(Mesh*, int ,int ,int, const TextAttrib&);
    void createBack(Mesh*, int ,int ,int, const TextAttrib&);
    void createX1(Mesh*, int,int,int, const TextAttrib&);
    void createX2(Mesh*, int,int,int, const TextAttrib&);
    void createQuad(Mesh*, Cubeside, int, int, int, const TextAttrib&);
    void createFace(const Vector3& p1,
                const Vector3& p2,
                const Vector3& p3,
                const Vector3& p4,
                const std::vector<Vector2>& t,
                const Vector3& n, float l, Mesh* m);
    bool hasSolidNeighbour(int,int,int,int,int,int);
    void buildBlockFaces(Mesh*, int, int, int, const TextAttrib&,bool, bool);
};

#endif