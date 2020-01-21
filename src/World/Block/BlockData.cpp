
#include "BlockData.h"

BlockData::BlockData(const std::string &fileName) {
    std::ifstream inFile("../assets/Blocks/" + fileName + ".block");

    if (!inFile.is_open()) {
        std::perror("Unable to open block file:");
        throw std::runtime_error("Unable to open block file: " + fileName +
                                 "!");
    }

    std::string line;
    while (std::getline(inFile, line)) {
        if (line == "TexTop") {
            int x, y;
            inFile >> x >> y;
            m_data.texTopCoord = Vector2((float)x, (float)y);
        }
        else if (line == "TexSide") {
            int x, y;
            inFile >> x >> y;
            m_data.texSideCoord = Vector2((float)x, (float)y);
        }
        else if (line == "TexBottom") {
            int x, y;
            inFile >> x >> y;
            m_data.texBottomCoord = Vector2((float)x, (float)y);
        }
        else if (line == "TexAll") {
            int x, y;
            inFile >> x >> y;
            m_data.texTopCoord= Vector2((float)x, (float)y);
            m_data.texSideCoord= Vector2((float)x, (float)y);
            m_data.texBottomCoord= Vector2((float)x, (float)y);
        }
        else if (line == "Id") {
            int id;
            inFile >> id;
            m_data.id = static_cast<BlockId>(id);
        }
        else if (line == "Opaque") {
            inFile >> m_data.isOpaque;
        }
        else if (line == "Collidable") {
            inFile >> m_data.isCollidable;
        }
        else if (line == "MeshType") {
            int id;
            inFile >> id;
            m_data.meshType = static_cast<BlockMeshType>(id);
        }
        else if (line == "ShaderType") {
            int id;
            inFile >> id;
            m_data.shaderType = static_cast<BlockShaderType>(id);
        }
    }
    m_data.ta.calculateTextDataBottom(m_data.texBottomCoord);
    m_data.ta.calculateTextDataTop(m_data.texTopCoord);
    m_data.ta.calculateTextDataLeft(m_data.texSideCoord);   
    m_data.ta.calculateTextDataRight(m_data.texSideCoord);
    m_data.ta.calculateTextDataFront(m_data.texSideCoord);
    m_data.ta.calculateTextDataBack(m_data.texSideCoord);
}

const BlockDataHolder &BlockData::getBlockData() const {
    return m_data;
}