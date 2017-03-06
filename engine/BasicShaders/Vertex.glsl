#version 430 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;

out vec4 color;
out vec3 fragmentPosition;

uniform mat4 Model2World;

void main(void)
{	
	gl_Position = Model2World * vec4(in_position, 1.0);
	color = in_color;
	fragmentPosition = gl_Position.xyz;
}
