#version 330

layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec2 in_TexCoords;

uniform mat4 ModelMatrix;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform float dayTime;

out vec2 passTextureCoord;

mat4 rotationX( in float angle ) {
	return mat4(	1.0,		0,			0,			0,
			 		0, 	cos(angle),	-sin(angle),		0,
					0, 	sin(angle),	 cos(angle),		0,
					0, 			0,			  0, 		1);
}

void main(){
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * rotationX(dayTime) * in_Position;

    passTextureCoord = in_TexCoords;
}