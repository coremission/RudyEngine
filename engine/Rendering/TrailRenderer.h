#ifndef TRAILRENDERER_h
#define TRAILRENDERER_h

#include "rendering.hpp"
#include <Model/GameObject.h>

class TrailMesh : public BaseMesh {
public:
	GLuint vbo;
	typedef glm::vec3 MeshData;
	std::vector<MeshData> data;

	TrailMesh(std::vector<glm::vec2> _points);
	~TrailMesh();
};

struct TrailMaterialTraits {
	static constexpr const char* ShaderProgramName = "trail_renderer_shader_prog";
	static constexpr const char* VertexShaderPath = "shaders/Vertex.glsl";
	static constexpr const char* FragmentShaderPath = "shaders/Fragment.glsl";
	typedef float PerVertexData;
	typedef std::vector<PerVertexData> MeshData;
	typedef TrailMesh Mesh;
};

class TrailRenderer : public Renderer<TrailRenderer, TrailMaterialTraits> {
	friend class Renderer<TrailRenderer, TrailMaterialTraits>;
	GameObject* gameObject;
public:
	explicit TrailRenderer(GameObject* gameObject);
	virtual ~TrailRenderer() override;
	virtual void render() const override;
	std::shared_ptr<TrailMesh> createMesh();
	virtual void update() override;
};

#endif //TRAILRENDERER_h
