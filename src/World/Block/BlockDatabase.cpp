#include "BlockDatabase.h"

BlockDatabase::BlockDatabase() : textureAtlas("blockatlas") {
    m_blocks[(int)BlockId::GRASS] = std::make_unique<DefaultBlock>("Grass");
    m_blocks[(int)BlockId::DIRT] = std::make_unique<DefaultBlock>("Dirt");
    m_blocks[(int)BlockId::STONE] = std::make_unique<DefaultBlock>("Stone");
    m_blocks[(int)BlockId::AIR] = std::make_unique<DefaultBlock>("Air");
    m_blocks[(int)BlockId::LEAVES] = std::make_unique<DefaultBlock>("Leaves");
    m_blocks[(int)BlockId::WOOD] = std::make_unique<DefaultBlock>("Wood");
    m_blocks[(int)BlockId::WOODBASE] = std::make_unique<DefaultBlock>("WoodBase");
    m_blocks[(int)BlockId::DIAMOND] = std::make_unique<DefaultBlock>("Diamond");
    m_blocks[(int)BlockId::REDSTONE] = std::make_unique<DefaultBlock>("Redstone");
    m_blocks[(int)BlockId::BEDROCK] = std::make_unique<DefaultBlock>("Bedrock");
    m_blocks[(int)BlockId::WATER] = std::make_unique<DefaultBlock>("Water");
    m_blocks[(int)BlockId::SAND] = std::make_unique<DefaultBlock>("Sand");
    m_blocks[(int)BlockId::CACTUS] = std::make_unique<DefaultBlock>("Cactus");
    m_blocks[(int)BlockId::GLASS] = std::make_unique<DefaultBlock>("Glass");
    m_blocks[(int)BlockId::DEADSHRUB] = std::make_unique<DefaultBlock>("DeadShrub");
    m_blocks[(int)BlockId::ROSE] = std::make_unique<DefaultBlock>("Rose");
    m_blocks[(int)BlockId::TALLGRASS] = std::make_unique<DefaultBlock>("TallGrass");
}

BlockDatabase &BlockDatabase::get(){
    static BlockDatabase d;
    return d;
}
/*const BlockType &getBlock(BlockType id) const {
	return GRASS;
}*/

const BlockType &BlockDatabase::getBlock(BlockId id) const {
    return *m_blocks[(int)id];
}

const BlockData &BlockDatabase::getData(BlockId id) const {
    return m_blocks[(int)id]->getData();
}