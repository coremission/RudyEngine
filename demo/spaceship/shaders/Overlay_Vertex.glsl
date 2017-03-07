#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;
layout (location = 2) in vec2 in_uv;

out vec4 color;
out vec3 fragmentPosition;
out vec2 uv;

uniform mat4 Model2World;
uniform mat4 Model2Projection;

void main(void)
{	
	gl_Position = Model2World * vec4(in_position, 1.0);
	color = in_color;
	uv = in_uv;
	fragmentPosition = gl_Position.xyz;
}
