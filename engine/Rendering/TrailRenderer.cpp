#include "TrailRenderer.h"
#include <iostream>

TrailMesh::TrailMesh(std::vector<glm::vec2> lineData):
	vbo(0)
{
    constexpr float TrailWidth = 0.01f;
	using namespace glm;

	// fill positions
	for (int i = 1; i < lineData.size(); ++i) {
		auto point = lineData[i];
		auto prevPoint = lineData[i - 1];

		auto _vector = point - prevPoint;
		auto p1 = prevPoint + normalize(vec2(-_vector.y, _vector.x)) * TrailWidth;
		auto p2 = prevPoint + normalize(vec2(_vector.y, -_vector.x)) * TrailWidth;
		auto p3 = point + normalize(vec2(-_vector.y, _vector.x)) * TrailWidth;
		auto p4 = point + normalize(vec2(_vector.y, -_vector.x)) * TrailWidth;

		data.push_back(vec3(p1, 0.0f));
		data.push_back(vec3(p2, 0.0f));
		data.push_back(vec3(p3, 0.0f));
		data.push_back(vec3(p4, 0.0f));
	}

	// 1. create vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 2. create vbo for vertex data
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// 3. fill data
	glBufferData(GL_ARRAY_BUFFER, sizeof(vec3) * data.size(), &data[0], GL_DYNAMIC_DRAW);

	// 4. bind attributes
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
    std::cout << "mesh vbo " << vbo << " created" << std::endl;
}

TrailMesh::~TrailMesh()
{
	std::cout << "delete trail mesh" << vao << std::endl;
	glDeleteVertexArrays(1, &vao);
}

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
    // draw line for a while
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//std::cout << "trail render" << std::endl;
}

std::shared_ptr<TrailMesh> TrailRenderer::createMesh()
{
    using namespace glm;
    
    std::vector<vec2> lineData = {
        vec2(-0.9f, -0.8f),
        vec2(-0.5f, 0.5f),
        vec2(0.0f, -0.5f),
        vec2(0.7f, 0.2f),
        vec2(0.8, -0.9f),
        vec2(1.0f, 1.0f)
    };
	std::vector<vec3> positions;
    
    auto result = std::make_shared<TrailMesh>(lineData);

	return result;
}

void TrailRenderer::update()
{
	using namespace glm;

	for(auto p: mesh->data)
	{
        //std::cout << p.x << " -> ";
		p += vec3(0.05f, 0.05f, 0);
        //std::cout << p.x;
	}

    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
    
    //glBufferData(GL_ARRAY_BUFFER, 0, nullptr, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * mesh->data.size(), &mesh->data[0]);
	
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    std::cout << "update mesh vbo " << mesh->vbo << std::endl;
}
