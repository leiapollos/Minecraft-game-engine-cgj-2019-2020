#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#include <string>
#include "../../Utils/NonCopyable.h"
#include "BlockId.h"
#include "../../vector2.h"
#include <fstream>
#include "../../TextAttrib.h"
enum class BlockMeshType {
    Cube = 0,
    X = 1,
};

enum class BlockShaderType {
    Chunk = 0,
    Liquid = 1,
    Flora = 2,
};

struct BlockDataHolder : public NonCopyable {
    BlockId id;
    Vector2 texTopCoord;
    Vector2 texSideCoord;
    Vector2 texBottomCoord;
    BlockMeshType meshType;
    BlockShaderType shaderType;
    TextAttrib ta;
    bool isOpaque;
    bool isCollidable;
};

class BlockData : public NonCopyable {
  public:
    BlockData(const std::string &fileName);

    const BlockDataHolder &getBlockData() const;

  private:
    BlockDataHolder m_data;

};

#endif // BLOCKDATA_H