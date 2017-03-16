#include "TrailRenderer.h"
#include <iostream>

TrailMesh::TrailMesh(size_t size):
	vbo(0)
{
	using namespace glm;
	data.resize(size);
	std::cout << std::endl << "data size: " << data.size() << std::endl;

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

TrailRenderer::TrailRenderer(GameObject* _gameObject, int _segmentsCount):
	Renderer(createMesh(_segmentsCount)), // triangle strip mesh
	gameObject(_gameObject),
	maxSegmentsCount(_segmentsCount),
	usedSegmentsCount(0)
{
	segments.resize(_segmentsCount);
	for (auto& s : segments)
		s = glm::vec2(0.0f, 0.0f);

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

	glDrawArrays(GL_TRIANGLE_STRIP, 0, usedSegmentsCount * 4);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//std::cout << "trail render" << std::endl;
}

std::shared_ptr<TrailMesh> TrailRenderer::createMesh(size_t size)
{
	auto result = std::make_shared<TrailMesh>(size * 4);
	return result;
}

void TrailRenderer::update()
{
	using namespace glm;
	
    // 1. Get current gameObject position
	auto objPos = vec2(gameObject->transform->getPosition());

	// 2. Compare with previously stored position
	if (length(objPos - segments[1]) > 0.05f) {
		std::cout << "emit " << usedSegmentsCount << std::endl;

		usedSegmentsCount = min(++usedSegmentsCount, maxSegmentsCount);
		// 2.1 shift positions and forget last
		for (int i = segments.size() - 1; i > 0; --i)
			segments[i] = segments[i - 1];
	}

	// 3. First segment is always sticked to gameObject
	segments[0] = objPos;
		
    // 3. if > threshold emit trail point
    
    // 4. adjust last segment to gameobject position (trail always must begin right behind gameobject)
    
    // 4. make smother angles
    // Step 5. Recalculate vbo data
    
	updateMeshData();
}

void TrailRenderer::updateMeshData()
{
	using namespace glm;
	constexpr float TrailWidth = 0.01f;

	// fill positions
	for (int i = 1; i < segments.size(); ++i) {
		auto point = segments[i];
		auto prevPoint = segments[i - 1];

		auto _vector = point - prevPoint;
		auto p1 = prevPoint + normalize(vec2(-_vector.y, _vector.x)) * TrailWidth;
		auto p2 = prevPoint + normalize(vec2(_vector.y, -_vector.x)) * TrailWidth;
		auto p3 = point + normalize(vec2(-_vector.y, _vector.x)) * TrailWidth;
		auto p4 = point + normalize(vec2(_vector.y, -_vector.x)) * TrailWidth;

		size_t meshIndex = 4 * (i - 1);
		mesh->data[meshIndex] = vec3(p1, 0.0f);
		mesh->data[meshIndex + 1] = vec3(p2, 0.0f);
		mesh->data[meshIndex + 2] = vec3(p3, 0.0f);
		mesh->data[meshIndex + 3] = vec3(p4, 0.0f);
	}

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vec3) * mesh->data.size(), &mesh->data[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}