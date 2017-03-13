#version 330 core

layout (location = 0) in vec3 in_position;

out vec4 color;
void main(void)
{	
	gl_Position = vec4(in_position, 1.0);
	color = vec4(1.0, 0, 0, 1.0);
}
