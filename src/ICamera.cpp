#include "ICamera.h"

ICamera::ICamera(GLuint _UBO_BP) {
	UBO_BP = _UBO_BP;
	glGenBuffers(1,&matricesVbo);
	glBindBuffer(GL_UNIFORM_BUFFER,matricesVbo); {
	    glBufferData(GL_UNIFORM_BUFFER, sizeof(std::array<float,16>) * 2, 0, GL_STREAM_DRAW);
	    glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, matricesVbo);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ICamera::~ICamera() {}

const ViewFrustum& ICamera::getFrustum() const {
    return m_frustum;
}