#include "Cloud.h"
#include <vector>

Clouds::Clouds() : cloud("clouds") {
    std::vector<GLfloat> mvertexCoords {
        -2048,  128, 2048,
        2048,  128, 2048,
        2048,  128, -2048,
        -2048,  128, -2048
    };

    std::vector<GLfloat> mtextureCoords {
        0, 2,
        2, 2,
        2, 0,
        0, 0,
    };

    std::vector<GLuint> mindexCoords {
        0, 2, 1,
        0, 3, 2
    };
    movement = 0.0f;
    m_cloud.addData({mvertexCoords, mtextureCoords, mindexCoords});
    m_shader.compileShaderFromFile("../src/shaders/clouds.vert", ShaderType::VERTEX);
    m_shader.compileShaderFromFile("../src/shaders/clouds.frag", ShaderType::FRAGMENT);
    m_shader.bindAttribLocation(VERTICES, "in_Position");
    m_shader.bindAttribLocation(TEXCOORDS, "in_TexCoords");
    m_shader.link();
    m_shader.addUniformBlock("SharedMatrices", 0);
    m_shader.detach();
}

void Clouds::Render(const ICamera& camera, float deltaTime, float lighting) {
    m_shader.use();
    m_cloud.bindVAO();
    cloud.bindTexture();
    //glBindTexture(GL_TEXTURE_2D, m_id);
    movement += deltaTime;
    
    if(movement > 1024) {
        movement = 0;
    }
    if(oldPos == Vector3() && camera.getPosition() != Vector3()) {
        oldPos = camera.getPosition();
    }

    if(abs((int)(camera.getPosition().x - oldPos.x)) > 1024) {
        oldPos.x = camera.getPosition().x;
    }

    if(abs((int)(camera.getPosition().z - oldPos.z)) > 1024) {
        oldPos.z = camera.getPosition().z;
    }
    
    //m_shader.loadLighting(g_info.lighting);
    m_shader.setUniform("lighting", lighting);
    GLint uniformID = m_shader.getUniformLocation("ModelMatrix");
    glUniformMatrix4fv(uniformID,1,GL_FALSE, MatrixFactory::translate(Vector3(oldPos.x, 0, oldPos.z + movement)).data);
    

    glDrawElements(GL_TRIANGLES, m_cloud.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
    //glDrawRangeElements(GL_TRIANGLES, 0, 3, 6, GL_UNSIGNED_INT, NULL);
}
