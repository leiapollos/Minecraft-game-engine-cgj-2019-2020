#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main()
{
    TexCoords = aPos;
    gl_Position = ProjectionMatrix * ViewMatrix * vec4(aPos, 1.0);
}  