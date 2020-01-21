#version 330 core

in vec2 ex_TexCoords;
in vec3 ex_Normal;
in float ex_CardinalLight;

out vec4 out_Color;
uniform sampler2D texSampler;
uniform sampler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

in float lightingO; 
in vec4 InWater0;
in vec4 FragPosLightSpace;
in float visibility;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float shadow = currentDepth > closestDepth  ? 1.0 : 0.0;

    return shadow;
}

void main(void)
{
	vec4 color = texture2D(texSampler, ex_TexCoords); 
	
	out_Color = vec4(color.rgb * lightingO * ex_CardinalLight * InWater0.rgb,1);

	//out_Color = vec4(mix(vec3(0.5f, 0.5f, 0.6f) * (lightingO*0.8),out_Color.rgb, visibility),out_Color.a);
    //out_Color.xyz += lightingO * (0.04, 0.03, 0.02);
    //if (out_Color.a == 0) discard;

	//out_Color = color*ex_CardinalLight;
	//color.w=0.15;
	if (out_Color.w == 0) discard;
}