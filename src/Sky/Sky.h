#ifndef SKY_H
#define SKY_H

#include "../ShaderProgram.h"
#include "../GameObject.h"
#include "../ICamera.h"
#include "../BasicTexture.h"
#include "../Model.h"

class Sky {
public:
	Sky();
	void Render(const ICamera& camera, float deltaTime);
private:

	Model m_SunModel;
	Model m_MoonModel;
	ShaderProgram m_shader;

	BasicTexture sun;
	BasicTexture moon;
};
#endif
