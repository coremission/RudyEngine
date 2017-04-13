#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;
layout (location = 2) in vec2 in_uv;

out vec4 color;
out vec2 uv;

uniform mat4 ViewProjection;

void main(void)
{	
	gl_Position = ViewProjection * vec4(in_position, 1.0);
	uv = in_uv;
	color = vec4(0.0, 1.0, 0, 1.0);
}
