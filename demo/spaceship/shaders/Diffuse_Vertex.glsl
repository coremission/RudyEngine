#version 330 core

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec4 in_color;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in vec3 in_normal;

out vec4 color;
out vec3 fragmentPosition;
out vec2 uv;

uniform mat4 Model2World;
uniform mat4 Model2Projection;

void main(void)
{	
	gl_Position = Model2Projection * vec4(in_position, 1.0);
	vec3 transformedNormal = vec3(Model2World * vec4(in_normal, 0.0));

	// half lambert
	color = in_color * ( dot(transformedNormal, vec3(1, 1, 1)) * 0.5 + 0.75 );
	uv = in_uv;
	fragmentPosition = gl_Position.xyz;
}
