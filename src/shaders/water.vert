#version 330

in vec4 in_Position;
in vec2 in_TexCoords;
in vec3 in_Normal;
in float in_CardinalLight;

out vec2 ex_TexCoords;
out vec3 ex_Normal;
out float ex_CardinalLight;
out float lightingO;

uniform float globalTime;

uniform mat4 ModelMatrix;
uniform float lighting;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

vec4 getWorldPos()
{
    vec4 inVert = ModelMatrix * vec4(in_Position.x,in_Position.y,in_Position.z,1);
    inVert.y += sin((globalTime + inVert.x) * 1.5) / 24.8f;
    inVert.y += cos((globalTime + inVert.z) * 1.5) / 24.1f;
    inVert.y -= 0.2;
    return inVert;
}

void main()
{
    gl_Position = ProjectionMatrix * ViewMatrix * getWorldPos();
    ex_TexCoords  = in_TexCoords;
    ex_Normal = in_Normal;
    ex_CardinalLight = in_CardinalLight;
    lightingO = lighting;
}