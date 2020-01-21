#ifndef MODEL_H
#define MODEL_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Utils/NonCopyable.h"
#include "Renderer/RenderInfo.h"
#include "Mesh.h"
#include <utility>
#include <vector>

struct ModelMesh
{
    std::vector<GLfloat> vertexPositions;
    std::vector<GLfloat> textureCoords;
    std::vector<GLuint>  indices;
};

class Model : public NonCopyable {
    public:
        Model() = default;
        Model(const ModelMesh& mesh);
        ~Model();

        Model(Model&& other);
        Model& operator= (Model&& other);

        void addData(const ModelMesh& mesh);

        void deleteData();

        void genVAO();
        void addEBO(const std::vector<GLuint>& indices);
        void addVBO(int dimensions, const std::vector<GLfloat>& data);
        void bindVAO() const;

        int getIndicesCount() const;

        const RenderInfo& getRenderInfo() const;

    private:
        RenderInfo m_renderInfo;

        int m_vboCount = 0;
        std::vector<GLuint> m_buffers;
};

#endif
