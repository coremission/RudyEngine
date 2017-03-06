#include "Mesh.h"
#include <glew/glew.h>

#define attribOffset(field) (reinterpret_cast<void *>(offsetof(VertexData, field)))

LegacyMesh::~LegacyMesh() {
	// delete VAO and VBOs
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	if(indexedMesh)
		glDeleteBuffers(1, &indicesVbo);
}

void LegacyMesh::bindAttribute(GLuint location, size_t size, int type, bool doNormalize, void* offset)
{
	glVertexAttribPointer(location, size, type, doNormalize ? GL_TRUE : GL_FALSE, sizeof(VertexData), offset);
	glEnableVertexAttribArray(location);
}

void LegacyMesh::fillVertexBuffer()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	bindAttribute(0, 3, GL_FLOAT, false, attribOffset(_position));
	bindAttribute(1, 4, GL_FLOAT, false, attribOffset(_color));
	bindAttribute(2, 2, GL_FLOAT, false, attribOffset(_uv));
	bindAttribute(3, 3, GL_FLOAT, true, attribOffset(_normal));
}

void LegacyMesh::fillIndicesBuffer()
{
	glGenBuffers(1, &indicesVbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesVbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

LegacyMesh::LegacyMesh(std::vector<VertexData> _vertices) 
	:indexedMesh(false), vertices(_vertices)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	fillVertexBuffer();

	glBindVertexArray(0);
}

LegacyMesh::LegacyMesh(std::vector<VertexData> _vertices, std::vector<GLuint> _indices)
	:indexedMesh(true), vertices(_vertices), indices(_indices)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	fillVertexBuffer();
	fillIndicesBuffer();

	glBindVertexArray(0);
}
