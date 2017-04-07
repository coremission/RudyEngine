#ifndef RUDY_RENDERING_HPP
#define RUDY_RENDERING_HPP

#include "ShaderProgram.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

// Basic interface to Use in GameObject
class IRenderer {
public:
	virtual void render() const {};
	virtual void update() {};
	virtual ~IRenderer() = default;
};

// Basic Mesh
class BaseMesh {
public:
	GLuint vao;
	BaseMesh();
	BaseMesh(GLuint _vao);
	virtual ~BaseMesh() = default; // there must be glDeleteArrayObjects
};

template<typename VertexData>
class Mesh: public BaseMesh {
	std::vector<VertexData> data;
};

template<typename DerivedRenderer, typename Traits>
class Renderer : public IRenderer {
protected:
	typename Traits::MeshData meshData;
	std::shared_ptr<typename Traits::Mesh> mesh;
	std::shared_ptr<ShaderProgram> shaderProgram;

	constexpr DerivedRenderer* derived() { return static_cast<DerivedRenderer*>(this); }
	// constructor
	Renderer(std::shared_ptr<typename Traits::Mesh>);
public:
	virtual void render() const override {
		// 1. bind mesh to context (bind VAO)

		// 2. use shader program

		// 3. set up uniform parameters

		// 4. draw (glDrawArrays, glDrawElements if mesh is indexed)
	};
	virtual ~Renderer() = default;
};

/////////////////////////////////// TEMPLATE DEFINITIONS///////////////////////////////////////////////////

template <typename DerivedRenderer, typename Traits>
Renderer<DerivedRenderer, Traits>::Renderer(std::shared_ptr<typename Traits::Mesh> _mesh):
	// 1. Load mesh
	mesh(_mesh),
	// 2. Load shader program
	shaderProgram(ShaderProgram::get(Traits::ShaderProgramName, Traits::VertexShaderPath, Traits::FragmentShaderPath))
{
	// 3. Validate shader program (IF DEBUG)
}

namespace rudy {
    void setUniformMat4(GLuint program, const std::string& name, glm::mat4 value);
}
#endif //RUDY_RENDERING_HPP
