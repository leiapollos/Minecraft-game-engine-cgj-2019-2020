#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "matrix4.h"
#include "MatrixFactory.h"
#include "ShaderProgram.h"
class ShadowMapping
{
private:
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMapFBO;
	unsigned int depthMap;
public:
	Matrix4 lightSpaceMatrix;
	ShadowMapping();
	void renderDepth(ShaderProgram* shader, Vector3 pos);
	void bindDepthMap();
	void quad(ShaderProgram* shader);
	unsigned int quadVAO = 0;
	unsigned int quadVBO;
	void renderQuad();
};

