#version 330 core

in vec2 ex_TexCoords;
in vec3 ex_Normal;
in float ex_CardinalLight;

out vec4 out_Color;
uniform sampler2D texSampler;
in float lightingO;


void main(void)
{
	float deltaDiscard = 0.01;
	float deltaT = 0.95;
	vec4 color = texture2D(texSampler, ex_TexCoords);
	out_Color = vec4(color.rgb * lightingO * ex_CardinalLight, color.a);
	if (out_Color.w <= deltaDiscard) discard;
	if (out_Color.w >= deltaT) out_Color.w = deltaT;
}