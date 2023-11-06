#version 430 core

layout (location = 0) in vec2 position;
layout (location = 1) in vec2 in_uv;

uniform vec4 offset;
uniform mat4 model;
uniform mat4 viewProj;

out vec2 uv;

void main()
{
	gl_Position = viewProj * model * (vec4(position, 0.0, 1.0) + offset);
	uv = in_uv;
}