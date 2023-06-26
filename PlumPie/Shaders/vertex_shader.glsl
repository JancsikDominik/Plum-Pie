#version 430 core

layout (location = 0) in vec2 position;

uniform vec4 offset;
uniform mat4 model;
uniform mat4 viewProj;

void main()
{
	gl_Position = viewProj * model * (vec4(position, 0.0, 1.0) + offset);
}