#version 330 core

in vec4 in_Position;
in vec2 in_TexCoords;
in vec3 in_Normal;
in float in_CardinalLight;

out vec2 ex_TexCoords;
out vec3 ex_Normal;
out float ex_CardinalLight;
out float lightingO;
out vec4 InWater0;
out vec4 FragPosLightSpace;
out float visibility;

uniform mat4 ModelMatrix;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

uniform float lighting;
uniform vec4 InWater;
uniform mat4 lightSpaceMatrix;

const float density = 0.009;
const float gradient = 1.4;

void main(void)
{
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	//vec4 positionRelative = ViewMatrix * ModelMatrix *in_Position;
    
	ex_TexCoords = in_TexCoords;
    ex_Normal = in_Normal;
    ex_CardinalLight = in_CardinalLight;
    lightingO = lighting;
	InWater0 = InWater;
	vec4 pos = ModelMatrix * in_Position;
	FragPosLightSpace = lightSpaceMatrix * pos;
	//float distance = length(positionRelative.xyz);
    //visibility = exp(-pow((distance*density), gradient)); // exponential
    //visibility = clamp(visibility, 0, 1); // min(max(x,minVal),maxVal)
}