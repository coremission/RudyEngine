#version 330 core

layout (location = 0) in vec4 in_position;
layout (location = 1) in vec3 offset;

out vec4 color;

void main(void)
{	
	gl_Position = in_position + vec4(offset, 0);
	color = vec4(1, 0, offset.x, 1);
}
