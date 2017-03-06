#include "rendering.hpp"

BaseMesh::BaseMesh() :
	vao(0)
{
}

BaseMesh::BaseMesh(GLuint _vao) :
	vao(_vao)
{
}