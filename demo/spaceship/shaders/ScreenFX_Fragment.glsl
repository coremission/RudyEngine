#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D screenTexture;

void main()
{
	vec4 texColor = texture(screenTexture, TexCoords);
	
	// Convert to grayscale using NTSC conversion weights
    float gray = dot(texColor.rgb, vec3(0.299, 0.587, 0.114));
    
    color = vec4(gray, gray, gray, texColor.a);
}
