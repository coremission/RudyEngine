#ifndef SPRITE_h
#define SPRITE_h
#include "Texture.h"
#include <memory>

class Sprite
{
private:
	std::shared_ptr<Texture> texture;
public:
	GLuint getTextureId() const { return texture->id; }

	explicit Sprite(std::shared_ptr<Texture>);
	~Sprite();
};

#endif //SPRITE_h