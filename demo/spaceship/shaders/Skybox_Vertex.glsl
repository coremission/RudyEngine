#version 330 core

layout (location = 0) in vec3 in_position;

out vec3 TexCoords;

uniform mat4 OrientationMatrix;

void main(void)
{
    gl_Position = OrientationMatrix * vec4(in_position, 1.0);  
    TexCoords = in_position;
}
