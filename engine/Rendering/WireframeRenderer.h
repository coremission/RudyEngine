#ifndef WIREFRAMERENDERER_h
#define WIREFRAMERENDERER_h

#include "rendering.hpp"

#include <vector>
#include <glm/glm.hpp>

class GameObject;

struct WireframeMaterialTraits {
	static constexpr const char* ShaderProgramName = "wireframe_shader_program";
	static constexpr const char* VertexShaderPath = "Shaders\\Skybox_Vertex.glsl";
	static constexpr const char* FragmentShaderPath = "Shaders\\Skybox_Fragment.glsl";
	// skybox is simple positions-only mesh (here must be glm::vec3);
	typedef glm::vec3 PerVertexData;
	typedef std::vector<PerVertexData> MeshData;
	typedef Mesh<PerVertexData> Mesh;
};

class WireframeRenderer : public Renderer<WireframeRenderer, WireframeMaterialTraits> {
	friend class Renderer<WireframeRenderer, WireframeMaterialTraits>;
public:
	explicit WireframeRenderer(GameObject* gameObject);
	virtual void render() const override;
	virtual ~WireframeRenderer() override;
};

#endif //WIREFRAMERENDERER_h