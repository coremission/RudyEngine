#include "SpriteRenderer.h"
#include "ShaderProgram.h"
#include "MeshManager.h"
#include "TextureManager.h"

#include <memory>
#include "Camera.h"

SpriteRenderer::SpriteRenderer(GameObject* _gameObject, const std::string& spriteFileName):
	Renderer(MeshManager::getDefaultSpriteMesh()),
	gameObject(_gameObject),
	spriteTexture(TextureManager::getTexture(spriteFileName))
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::render(const Camera* const camera) const
{
	// 1. bind vao
	glBindVertexArray(mesh->vao);

	// 2. use program
	GLuint program = shaderProgram->programId();
	glUseProgram(program);

	// 3. set active textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, spriteTexture->id);

	// 3.1 set uniform variables
	GLuint mwLocation = glGetUniformLocation(program, "Model2World");
	glm::mat4 model2World = gameObject->transform->getLocalToWorldMatrix();
	glUniformMatrix4fv(mwLocation, 1, GL_FALSE, &model2World[0][0]);

	GLuint mvpLocation = glGetUniformLocation(program, "Model2Projection");
	glm::mat4 viewProjectionMatrix = camera->getViewProjectionMatrix();
	glm::mat4 viewMatrix = camera->getViewMatrix();

	glm::mat4 mvpMatrix = viewProjectionMatrix * model2World;
	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &mvpMatrix[0][0]);

	// 4. draw 6 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// 5. unbind program, texture and VAO
	glUseProgram(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}