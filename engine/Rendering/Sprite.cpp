#include "Sprite.h"

Sprite::Sprite(std::shared_ptr<Texture> _texture):
	texture(_texture)
{
}

Sprite::~Sprite()
{
}
