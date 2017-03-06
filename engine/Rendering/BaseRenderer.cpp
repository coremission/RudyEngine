#include "BaseRenderer.h"
#include "Camera.h"
#include <iostream>
#include "TextureManager.h"
using namespace std;

BaseRenderer::BaseRenderer(GameObject* gameObject, shared_ptr<ShaderProgram> _material, shared_ptr<LegacyMesh> _mesh, const std::string& diffuseTextureFilename):
	_gameObject(gameObject), mesh(_mesh), material(_material), diffuseTexture(TextureManager::getTexture(diffuseTextureFilename))
{
}

BaseRenderer::~BaseRenderer()
{
}

void BaseRenderer::render() const
{
	glBindVertexArray(mesh->vao);

	GLuint program = material->programId();
	glUseProgram(program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture->id);

	GLuint m2wLocation = glGetUniformLocation(program, "Model2World");
	glm::mat4 modelingMatrix = _gameObject->transform->getLocalToWorldMatrix();
	glUniformMatrix4fv(m2wLocation, 1, GL_FALSE, &modelingMatrix[0][0]);

	GLuint mvpLocation = glGetUniformLocation(program, "Model2Projection");
	glm::mat4 viewProjectionMatrix = Camera::getMainCamera()->getViewProjectionMatrix();
	glm::mat4 viewMatrix = Camera::getMainCamera()->getViewMatrix();

	glm::mat4 mvpMatrix = viewProjectionMatrix * modelingMatrix;
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvpMatrix[0][0]);
	
	if (mesh->isIndexed())
		glDrawElements(GL_TRIANGLES, mesh->indicesCount(), GL_UNSIGNED_INT, reinterpret_cast<void *>(0));
	else
		glDrawArrays(GL_TRIANGLES, 0, mesh->verticesCount());
}

std::unique_ptr<BaseRenderer> BaseRenderer::create(GameObject* gameObject, std::shared_ptr<ShaderProgram> material, std::shared_ptr<LegacyMesh> mesh, const std::string& diffuseTextureFilename)
{
	return std::make_unique<BaseRenderer>(gameObject, material, mesh, diffuseTextureFilename);
}
