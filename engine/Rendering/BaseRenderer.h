#ifndef BASERENDERER_h
#define BASERENDERER_h
#include <Model/GameObject.h>
#include "ShaderProgram.h"
#include "Mesh.h"
#include "rendering.hpp"
#include "Texture.h"

#include <memory>

class GameObject;

class BaseRenderer: public IRenderer
{
protected:
	const GameObject* const _gameObject;

public:
	std::shared_ptr<LegacyMesh> mesh;
	std::shared_ptr<ShaderProgram> material;
	std::shared_ptr<Texture> diffuseTexture;

	BaseRenderer(GameObject* gameObject, std::shared_ptr<ShaderProgram>, std::shared_ptr<LegacyMesh> mesh, const std::string& diffuseTextureFilename);
	virtual ~BaseRenderer();
	virtual void render(const Camera* const camera) const override;

	static std::unique_ptr<BaseRenderer> create(GameObject* gameObject, std::shared_ptr<ShaderProgram> material, std::shared_ptr<LegacyMesh> mesh, const std::string& diffuseTextureFilename);
};

#endif // BASERENDERER_h
