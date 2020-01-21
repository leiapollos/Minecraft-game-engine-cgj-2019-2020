#version 330

in vec3 in_Position;
in vec2 in_TexCoords;
out vec2 ex_TexCoords;


uniform mat4 ModelMatrix;

uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main()
{
    vec4 worldPos = ModelMatrix * vec4(in_Position, 1.0);
    worldPos.y += 0.5;
    gl_Position = ProjectionMatrix * ViewMatrix * worldPos;

    ex_TexCoords = in_TexCoords;
}
