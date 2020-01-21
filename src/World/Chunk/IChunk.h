#ifndef ICHUNK_H
#define ICHUNK_H
class Mesh;
//class BlockType;
//class BlockId;
#include <cstdint>

using Block_t = uint8_t;

enum class BlockId: Block_t;
struct IChunk {
	virtual BlockId getBlock(int x, int y, int z) = 0;
	virtual void setBlock(const Vector3& pos, const BlockId block) = 0;

};
#endif