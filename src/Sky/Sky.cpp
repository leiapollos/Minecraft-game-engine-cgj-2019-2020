#include "Sky.h"
#define degreesToRadians(x) x*(3.141592f/180.0f)

Sky::Sky() : sun("Sun"), moon("Moon") {
	std::vector<GLfloat> svertexCoords
	{
		-50,  50, 400,
		50,  50, 400,
		50, -50, 400,
		-50, -50, 400
	};

	std::vector<GLfloat> stextureCoords
	{
		0, 1,
		1, 1,
		1, 0,
		0, 0,
	};

	std::vector<GLuint> sindexCoords
	{
		0, 1, 2,
		2, 3, 0
	};

	std::vector<GLfloat> mvertexCoords
	{
		-50,  50, -400,
		50,  50, -400,
		50, -50, -400,
		-50, -50, -400
	};

	std::vector<GLfloat> mtextureCoords
	{
		0, 1,
		1, 1,
		1, 0,
		0, 0,
	};

	std::vector<GLuint> mindexCoords
	{
		2, 1, 0,
		0, 3, 2
	};

	m_SunModel.addData({ svertexCoords, stextureCoords, sindexCoords });
	m_MoonModel.addData({ mvertexCoords, mtextureCoords, mindexCoords });

	m_shader.compileShaderFromFile("../src/shaders/sun.vert", ShaderType::VERTEX);
	m_shader.compileShaderFromFile("../src/shaders/sun.frag", ShaderType::FRAGMENT);
	m_shader.bindAttribLocation(VERTICES, "in_Position");
	m_shader.bindAttribLocation(TEXCOORDS, "in_TexCoords");
	m_shader.link();
	m_shader.addUniformBlock("SharedMatrices", 0);
	m_shader.detach();
}

void Sky::Render(const ICamera& camera, float deltaTime) {
	deltaTime = fmodf(deltaTime, 300.0f);
	//glEnable(GL_BLEND);
	m_shader.use();
	m_SunModel.bindVAO();
	sun.bindTexture();

	GLint uniformID = m_shader.getUniformLocation("ModelMatrix");
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, MatrixFactory::translate(camera.getPosition()).data);
	m_shader.setUniform("dayTime", degreesToRadians((deltaTime / 300) * 360));

	/*m_shader.loadModelMatrix(transformMatrix);
	m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
	m_shader.loadTime(degreesToRadians(((float)dayTime / 24000) * 360));*/

	glDrawElements(GL_TRIANGLES, m_SunModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);

	m_shader.use();
	m_MoonModel.bindVAO();
	moon.bindTexture();

	uniformID = m_shader.getUniformLocation("ModelMatrix");
	glUniformMatrix4fv(uniformID, 1, GL_FALSE, MatrixFactory::translate(camera.getPosition()).data);
	m_shader.setUniform("dayTime", degreesToRadians((deltaTime / 300) * 360));
	/*m_shader.loadModelMatrix(transformMatrix);
	m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());
	m_shader.loadTime(degreesToRadians(((float)dayTime / 24000) * 360));*/

	glDrawElements(GL_TRIANGLES, m_MoonModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	//glDisable(GL_BLEND);
}