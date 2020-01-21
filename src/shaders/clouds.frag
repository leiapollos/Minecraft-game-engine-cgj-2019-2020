#version 330

out vec4 out_Color;
in vec2 ex_TexCoords;

uniform sampler2D texSampler;
vec4 color;
uniform float lighting;

void main()
{
    color = texture(texSampler, ex_TexCoords);
    //Lighting Calculations
    out_Color = vec4(color.rgb*1.8f*lighting, color.a * 0.6); 
    if (out_Color.a == 0) discard;
}
