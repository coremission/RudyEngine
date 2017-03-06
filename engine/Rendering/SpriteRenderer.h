#ifndef SPRITERENDERER_h
#define SPRITERENDERER_h

#include "rendering.hpp"
#include "Sprite.h"
#include <Model/GameObject.h>
#include <memory>

struct SpriteMaterialTraits {
	static constexpr const char * ShaderProgramName = "default_sprite_shader_prog";
	static constexpr const char * VertexShaderPath = "Shaders\\Vertex.glsl";
	static constexpr const char * FragmentShaderPath = "Shaders\\Fragment.glsl";
	typedef float PerVertexData;
	typedef std::vector<PerVertexData> MeshData;
	typedef Mesh<PerVertexData> Mesh;
};

class SpriteRenderer: public Renderer<SpriteRenderer, SpriteMaterialTraits>
{
	friend class Renderer<SpriteRenderer, SpriteMaterialTraits>;
	GameObject* gameObject;
	std::shared_ptr<Texture> spriteTexture;
public:
	SpriteRenderer(GameObject* gameObject, const std::string& spriteFileName);
	virtual ~SpriteRenderer() override;
	virtual void render() const override;
};

#endif //SPRITERENDERER_h