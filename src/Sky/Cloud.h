#ifndef CLOUD_H
#define CLOUD_H

#include "../ShaderProgram.h"
#include "../GameObject.h"
#include "../ICamera.h"
#include "../BasicTexture.h"
#include "../Model.h"

class Camera;

class Clouds {
	public:
	    Clouds();

	    void Render(const ICamera& camera, float deltaTime,float lighting);
	private:
	    ShaderProgram m_shader;
	    BasicTexture cloud;
	    Model m_cloud;
	    Vector3 oldPos;
	    float movement;
	};

#endif