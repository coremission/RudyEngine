#include "TrailRenderer.h"
#include "Camera.h"
#include "TextureManager.h"

#include <iostream>

#define attribOffset(field) (reinterpret_cast<void *>(offsetof(TrailMesh::MeshDataType, field)))
constexpr int VerticesPerSegment = 2;

void bindAttribute(GLuint location, size_t size, int type, bool doNormalize, void* offset)
{
    glVertexAttribPointer(location, size, type, doNormalize ? GL_TRUE : GL_FALSE, sizeof(TrailMesh::MeshDataType), offset);
    glEnableVertexAttribArray(location);
}

TrailMesh::TrailMesh(size_t size):
	vbo(0)
{
	using namespace glm;
	data.resize(size); // make mesh data buffer its fixed size
	std::cout << "mesh size: " << data.size() << std::endl;

	// 1. create vao
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// 2. create vbo for vertex data
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	// 3. fill data
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshDataType) * data.size(), &data[0], GL_DYNAMIC_DRAW);

	// 4. bind attributes
    bindAttribute(0, 3, GL_FLOAT, false, attribOffset(position));
    bindAttribute(1, 4, GL_FLOAT, false, attribOffset(color));
    bindAttribute(2, 2, GL_FLOAT, true, attribOffset(uv));
    
	glBindVertexArray(0);
    std::cout << "mesh vbo: " << vbo << " created" << std::endl;
}

TrailMesh::~TrailMesh()
{
	std::cout << "mesh vao deleted: " << vao << std::endl;
	glDeleteVertexArrays(1, &vao);
}

TrailRenderer::TrailRenderer(GameObject* _gameObject, int _segmentsCount, const std::string& textureFileName):
	Renderer(createMesh(_segmentsCount)), // triangle strip mesh
	gameObject(_gameObject),
	maxSegmentsCount(_segmentsCount),
	usedSegmentsCount(0),
	texture(TextureManager::getTexture(textureFileName))
{
	segments.resize(_segmentsCount);
	for (auto& s : segments)
		s = glm::vec3(0.0f, 0.0f, 0.0f);
}

TrailRenderer::~TrailRenderer()
{
}

void TrailRenderer::render() const {
    // there must be at least 2 segments to get something drawable
	if (usedSegmentsCount < 2)
		return;

	// 1. bind skybox vao
	glBindVertexArray(mesh->vao);

	// 2. use skybox program
	glUseProgram(shaderProgram->programId());

	// 2.1 draw triangle strip
    // draw line for a while
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 3. set active textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture->id);

	// 4. fill uniform variables
    glm::mat4 viewProjectionMatrix = Camera::getMainCamera()->getViewProjectionMatrix();
	rudy::setUniformMat4(shaderProgram->programId(), "ViewProjection", viewProjectionMatrix);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, usedSegmentsCount * VerticesPerSegment);
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	//std::cout << "trail render " << usedSegmentsCount << std::endl;
}

std::shared_ptr<TrailMesh> TrailRenderer::createMesh(size_t segmentsCount) {
	auto result = std::make_shared<TrailMesh>(segmentsCount * VerticesPerSegment);
	return result;
}

void TrailRenderer::update() {
	using namespace glm;
	
    // 1. Get current gameObject position
	auto objPos = gameObject->transform->getPosition();

	// 2. Compare with previously stored position (emit new segment)
	if (usedSegmentsCount < 2 || length(objPos - segments[1]) > 0.58f) {
		usedSegmentsCount = min(++usedSegmentsCount, maxSegmentsCount);
		// 2.1 shift positions and forget last
		for (int i = segments.size() - 1; i > 0; --i)
			segments[i] = segments[i - 1];
	}

	// 3. First segment is always sticked to gameObject
	segments[0] = objPos;
    
	// 4. fade out trail
	if (usedSegmentsCount > 1) {
		auto& lastSegmentPos = segments[usedSegmentsCount - 1];
		auto preLastSegmentPos = segments[usedSegmentsCount - 2];

		auto lastSegmentVector = preLastSegmentPos - lastSegmentPos;
		float segmentLength = length(lastSegmentVector);
		constexpr float fadeOutSpeed = 0.002f;
		if(segmentLength < fadeOutSpeed) {
			--usedSegmentsCount;
		}
		else {
			lastSegmentPos += normalize(lastSegmentVector) * fadeOutSpeed;
		}
	}
    
    // 5. make smoother angles
    /*constexpr float smoothFactor = 0.01f;
    
    for(int i = 0; i < usedSegmentsCount - 2 && i < segments.size() - 2; ++i) {
        auto& first = segments[i];
        auto& second = segments[i + 1];
        auto& third = segments[i + 2];
        
        auto middle = (first + third) * 0.5f;
        second = (1 - smoothFactor) * second + smoothFactor * middle;
    }*/
	
    // 6. Recalculate vbo data
    updateMeshData();
}


/*
 todo: This logic can be implemented on GPU side with Vertex shader with instance data array as for particles
 */
void TrailRenderer::updateMeshData() {
	using namespace glm;
	constexpr float TrailWidth = 0.1f;

	// fill positions
	for (int i = 0; i < segments.size() && i < usedSegmentsCount; ++i) {
		bool isLastSegment = i == segments.size() - 1;
		auto point = segments[i];
		auto nextPoint = segments[isLastSegment ? i - 1 : i + 1]; // take prev point for last to get direction

		auto deltaVector = point - nextPoint;
        
		float segmentWidth = TrailWidth;// *((segments.size() - i) / static_cast<float>(segments.size())); // narrower at the end of trail
		auto p1 = point + normalize(vec3(-deltaVector.y, deltaVector.x, point.z)) * segmentWidth;
		auto p2 = point + normalize(vec3(deltaVector.y, -deltaVector.x, nextPoint.z)) * segmentWidth;

		size_t meshIndex = VerticesPerSegment * i;
		
		if (!isLastSegment) {
			mesh->data[meshIndex].position = p1;
			mesh->data[meshIndex].color = vec4(0, 1, 0, 1);
            mesh->data[meshIndex + 1].position = p2;
			mesh->data[meshIndex + 1].color = vec4(0, 1, 0, 1);
		}
		else { // must be flipped for last segment to get nicely closed last segment 'ribbon'
			mesh->data[meshIndex].position = p2;
			mesh->data[meshIndex].color = vec4(1, 0, 1, 1);
			mesh->data[meshIndex + 1].position = p1;
			mesh->data[meshIndex + 1].color = vec4(1, 0, 1, 1);
            mesh->data[meshIndex].uv = vec2(0, 1);
            mesh->data[meshIndex + 1].uv = vec2(1, 0);
		}
	}
    
 	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(VertexDataType) * mesh->data.size(), &mesh->data[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
