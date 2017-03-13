#include "TrailRenderer.h"
#include <iostream>

TrailRenderer::TrailRenderer(GameObject* _gameObject):
	Renderer(createMesh()), // triangle strip mesh
	gameObject(_gameObject)
{
}

TrailRenderer::~TrailRenderer()
{
}

void TrailRenderer::render() const
{
	// 1. bind skybox vao
	glBindVertexArray(mesh->vao);

	// 2. use skybox program
	glUseProgram(shaderProgram->programId());

	// 3. draw triangle strip
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

	std::cout << "trail render" << std::endl;
}

std::shared_ptr<BaseMesh> TrailRenderer::createMesh()
{
	std::vector<glm::vec3> positions;
	// fill positions
	positions.push_back(glm::vec3(0.1f, 0.5f, 0.5f));
	positions.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
	positions.push_back(glm::vec3(0.7f, 0.2f, 0.5f));

	// 1. create vao
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 2. create vbo for vertex data
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// 3. fill data
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * positions.size(), &positions[0], GL_STATIC_DRAW);

	// 4. bind attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	auto result = std::make_shared<BaseMesh>(vao);

	return result;
}