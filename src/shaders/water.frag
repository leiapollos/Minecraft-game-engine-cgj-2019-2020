#version 330 core

in vec2 ex_TexCoords;
in vec3 ex_Normal;
in float ex_CardinalLight;

out vec4 out_Color;
uniform sampler2D texSampler;
in float lightingO;


void main(void)
{
	vec4 color = texture2D(texSampler, ex_TexCoords);
	color = color*lightingO *ex_CardinalLight;
	color.w=0.65;
	out_Color = color;
}