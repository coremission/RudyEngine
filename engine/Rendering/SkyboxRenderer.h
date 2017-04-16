#ifndef SKYBOXRENDERER_h
#define SKYBOXRENDERER_h

#include "Camera.h"
#include "rendering.hpp"

#include <vector>
#include <glm/glm.hpp>

struct SkyboxMaterialTraits {
	static constexpr const char* ShaderProgramName = "skybox_shader_program";
	static constexpr const char* VertexShaderPath = "Shaders\\Skybox_Vertex.glsl";
	static constexpr const char* FragmentShaderPath = "Shaders\\Skybox_Fragment.glsl";
	// skybox is simple positions-only mesh (here must be glm::vec3);
	using VertexDataType = glm::vec3;
	using MeshType = BaseMesh;
};

class SkyboxRenderer : public Renderer<SkyboxRenderer, SkyboxMaterialTraits> {
	// skybox
	GLuint cubeMapTextureId;

	friend class Renderer<SkyboxRenderer, SkyboxMaterialTraits>;
	GLuint createCubemap(std::vector<std::string> filenames);
public:
	explicit SkyboxRenderer(std::vector<std::string> filenames);
	virtual void render(const Camera* const camera) const override;
	virtual ~SkyboxRenderer() override;
};

#endif //SKYBOXRENDERER_h