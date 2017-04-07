#include "rendering.hpp"

BaseMesh::BaseMesh() :
	vao(0)
{
}

BaseMesh::BaseMesh(GLuint _vao) :
	vao(_vao)
{
}

// todo: no need to pass std::string and then get c_str()
void rudy::setUniformMat4(GLuint program, const std::string& name, glm::mat4 value) {
    GLuint location = glGetUniformLocation(program, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}
