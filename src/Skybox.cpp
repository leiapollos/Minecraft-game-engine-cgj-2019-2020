#include "Skybox.h"

unsigned int Skybox::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	//int width, height, nrChannels;
	sf::Image img;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		if (!img.loadFromFile(faces[i])) {
			std::cout << "ErrorSkybox?\n";
			///@TODO Throw error
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0, GL_RGBA, img.getSize().x, img.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img.getPixelsPtr()
		);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

Skybox::Skybox(ShaderProgram* shader_)
{
	shader = shader_;
	faces =
	{
		"../assets/skybox/Dia/dm.png",
        "../assets/skybox/Dia/dm.png",
        "../assets/skybox/Dia/dt.png",
        "../assets/skybox/Dia/db.png",
        "../assets/skybox/Dia/dm.png",
        "../assets/skybox/Dia/dm.png"
		/*"../assets/skybox/right.jpg",
		"../assets/skybox/left.jpg",
		"../assets/skybox/top.jpg",
		"../assets/skybox/bottom.jpg",
		"../assets/skybox/front.jpg",
		"../assets/skybox/back.jpg"*/
	};

	cubemapTexture = loadCubemap(faces);
	//cubemapTexture1 = loadCubemap(faces1);

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	//shader->use();
}

void Skybox::draw(ICamera* camera, Matrix4* projM, float time)
{
	Matrix4 view = camera->getViewMatrix();
	view.set(3, 0, 0);
	view.set(3, 1, 0);
	view.set(3, 2, 0);
	view.set(3, 3, 1);
	view.set(0, 3, 0);
	view.set(1, 3, 0);
	view.set(2, 3, 0);
	camera->setViewMatrix(view);
	camera->setProjectionMatrix(*projM);

	glDepthMask(GL_FALSE);
	shader->use();
	shader->setUniform("dayTime", time);
	glBindVertexArray(skyboxVAO);
	//if(glfwGetTime() < 60)
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	/*else
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture1);*/
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glDepthMask(GL_TRUE);
}
