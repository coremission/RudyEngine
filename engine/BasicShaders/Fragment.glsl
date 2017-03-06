#version 430 core
layout (location = 0) out vec4 out_color;
in vec4 color;
in vec3 fragmentPosition;

uniform float time;

void main(void)
{
  out_color = color + vec4(cos(time + fragmentPosition.x) * 0.5f, cos(time + fragmentPosition.y) * 0.5f, cos(time) * 0.5f, 0.0f);
}
