#ifndef TRAILRENDERER_h
#define TRAILRENDERER_h

#include "rendering.hpp"
#include <Model/GameObject.h>

class TrailMesh : public BaseMesh {
public:
	GLuint vbo;
    struct MeshDataType{
        glm::vec3 position;
        glm::vec4 color;
		glm::vec2 uv;
    };
	std::vector<MeshDataType> data;
	TrailMesh(size_t size);
	virtual ~TrailMesh() override;
};

struct TrailMaterialTraits {
	static constexpr const char* ShaderProgramName = "trail_renderer_shader_prog";
	static constexpr const char* VertexShaderPath = "shaders/TrailVertex.glsl";
	static constexpr const char* FragmentShaderPath = "shaders/TrailFragment.glsl";
	using VertexDataType = TrailMesh::MeshDataType;
	using MeshType = TrailMesh;
};

class TrailRenderer : public Renderer<TrailRenderer, TrailMaterialTraits> {
	friend class Renderer<TrailRenderer, TrailMaterialTraits>;
	GameObject* gameObject;
	int maxSegmentsCount;
	int usedSegmentsCount;
	float trailWidth;
	std::vector<glm::vec3> segments;
	std::shared_ptr<Texture> texture;
public:
	explicit TrailRenderer(GameObject* _gameObject, int _segmentsCount, float _trailWidth, const std::string& textureFileName);
	virtual ~TrailRenderer() override;
	virtual void render() const override;
	std::shared_ptr<TrailMesh> createMesh(size_t size);
	virtual void update() override;
	void updateMeshData();
};

#endif //TRAILRENDERER_h
