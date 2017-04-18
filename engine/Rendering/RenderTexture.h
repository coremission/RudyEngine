#ifndef RENDERTEXTURE_h
#define RENDERTEXTURE_h
#include <glad/glad.h>

class RenderTexture {
	GLuint fbo;
	GLuint texture;
	GLuint depthStencilTexture;
	int width;
	int height;

public:
	RenderTexture(int _width, int _height);
	~RenderTexture();

	void bind();
	GLuint getTextureId() { return texture; };
};
#endif //RENDERTEXTURE_h