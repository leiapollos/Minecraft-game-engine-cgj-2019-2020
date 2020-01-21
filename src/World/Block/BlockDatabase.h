#ifndef BLOCKDATABASE_H
#define BLOCKDATABASE_H

#include <array>
#include <memory>
#include "../../Utils/Singleton.h"
#include "BlockId.h"
#include "BlockData.h"
#include "BlockType.h"
#include "../../TextureAtlas.h"
class BlockDatabase : public Singleton {
  
  public:
    static BlockDatabase &get();

	const BlockType &getBlock(BlockId id) const;
    const BlockData &getData(BlockId id) const;
    TextureAtlas textureAtlas;
  private:

    BlockDatabase();

    std::array<std::unique_ptr<BlockType>, (unsigned)BlockId::NUM_TYPES>
        m_blocks;
};

#endif // BLOCKDATABASE_H