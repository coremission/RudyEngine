#include "OverlayRenderer.h"
#include "ShaderProgram.h"
#include "MeshManager.h"
#include "TextureManager.h"

#include <memory>
#include "Camera.h"

OverlayRenderer::OverlayRenderer(GameObject* _gameObject, const std::string& spriteFileName):
	Renderer(MeshManager::getDefaultSpriteMesh()),
	gameObject(_gameObject),
	spriteTexture(TextureManager::getCompressedTexture(spriteFileName))
{
}

OverlayRenderer::~OverlayRenderer()
{
}

void OverlayRenderer::render() const
{
	// 1. bind vao
	glBindVertexArray(mesh->vao);

	// 2. use program
	GLuint program = shaderProgram->programId();
	glUseProgram(program);

	// 3. fill uniform variables
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, spriteTexture->id);

	GLuint mwLocation = glGetUniformLocation(program, "Model2World");
	glm::mat4 model2World = gameObject->transform->getLocalToWorldMatrix();
	glUniformMatrix4fv(mwLocation, 1, GL_FALSE, &model2World[0][0]);

	GLuint mvpLocation = glGetUniformLocation(program, "Model2Projection");
	glm::mat4 viewProjectionMatrix = Camera::getMainCamera()->getViewProjectionMatrix();
	glm::mat4 viewMatrix = Camera::getMainCamera()->getViewMatrix();

	glm::mat4 mvpMatrix = viewProjectionMatrix * model2World;
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

	// 4. draw 6 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// 5. unbind program, texture and VAO
	glUseProgram(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}