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
    };
	std::vector<MeshDataType> data;

	TrailMesh(size_t size);
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
	int maxSegmentsCount;
	int usedSegmentsCount;
	std::vector<glm::vec2> segments;
public:
	explicit TrailRenderer(GameObject* gameObject, int _segmentsCount);
	virtual ~TrailRenderer() override;
	virtual void render() const override;
	std::shared_ptr<TrailMesh> createMesh(size_t size);
	virtual void update() override;
	void updateMeshData();
};

#endif //TRAILRENDERER_h
