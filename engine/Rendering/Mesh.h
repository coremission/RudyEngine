#ifndef MESH_h
#define MESH_h

#include "rendering.hpp"
#include <Model/VertexData.h>

#include <vector>
#include <glad/glad.h>

class LegacyMesh: public BaseMesh
{
private:
	bool indexedMesh;
	std::vector<VertexData> vertices;
	std::vector<GLuint> indices;
	GLuint vbo;
	GLuint indicesVbo;

	void fillVertexBuffer();
	void fillIndicesBuffer();
	
	static void bindAttribute(GLuint location, size_t size, int type, bool doNormalize, void* offset);
public:
	LegacyMesh(std::vector<VertexData>);
	LegacyMesh(std::vector<VertexData>, std::vector<GLuint>);
	virtual ~LegacyMesh() override;
	int verticesCount() const { return vertices.size(); }
	int indicesCount() const { return indices.size(); }
	bool isIndexed() const { return indexedMesh; }
};

#endif//MESH_h
