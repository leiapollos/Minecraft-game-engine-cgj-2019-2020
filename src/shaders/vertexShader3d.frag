#version 330 core

out vec4 out_Color;
in vec4 ex_Color;


void main(void)
{
	out_Color = ex_Color;
}