﻿#ifndef WIREFRAMERENDERER_h
#define WIREFRAMERENDERER_h

#include "rendering.hpp"
#include <glm/glm.hpp>

class GameObject;

struct WireframeMaterialTraits {
	static constexpr const char* ShaderProgramName = "wireframe_shader_program";
	static constexpr const char* VertexShaderPath = "Shaders\\Skybox_Vertex.glsl";
	static constexpr const char* FragmentShaderPath = "Shaders\\Skybox_Fragment.glsl";
	using VertexDataType = glm::vec3;
	using MeshType = Mesh<VertexDataType>;
};

class WireframeRenderer : public Renderer<WireframeRenderer, WireframeMaterialTraits> {
	friend class Renderer<WireframeRenderer, WireframeMaterialTraits>;
public:
	explicit WireframeRenderer(GameObject* gameObject);
	virtual void render(const Camera* const camera) const override;
	virtual ~WireframeRenderer() override;
};

#endif //WIREFRAMERENDERER_h