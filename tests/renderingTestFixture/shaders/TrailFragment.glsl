#version 330 core
layout (location = 0) out vec4 out_color;
in vec4 color;
in vec2 uv;

uniform sampler2D mySampler;

void main(void)
{
  out_color = color + texture(mySampler, vec2(uv.x, uv.y));
}
