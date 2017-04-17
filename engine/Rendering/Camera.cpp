#include "Camera.h"
#include "Model/Transform.h"
#include "SkyboxRenderer.h"

#include <glm/gtx/transform.hpp>
#include <vector>
#include <memory>
#include <Rendering/MeshManager.h>
#include <Rendering/ShaderLoader.h>
#include <Rendering/TextureManager.h>

Camera::Camera(GameObject* go)
	:Component(go), 
	horizontalFov(45), 
	ratio(4.0f/3.0f), 
	nearClippingPlane(1.0f), 
	farClippingPlane(100.0f),
	clearMethod(ClearMethod::SolidColor)
{
	rudy::registerCamera(this);
	recalculateMatrices();
}

Camera::Camera(GameObject * _gameObject, float _fov, float _ratio, float _near, float _far)
	:Component(_gameObject), 
	horizontalFov(_fov), 
	ratio(_ratio),
	nearClippingPlane(_near),
	farClippingPlane(_far),
	clearMethod(ClearMethod::SolidColor)
{
	rudy::registerCamera(this);
	recalculateMatrices();
}

void Camera::Update()
{
}

void Camera::Start()
{
}

glm::mat4 Camera::getViewProjectionMatrix() const {
	recalculateMatrices();
	return projectionMatrix * viewMatrix;
}

glm::mat4 Camera::getOrientationMatrix() const {
	recalculateMatrices();
	// todo: while orientation isn't tuned for camera control
	//return getViewProjectionMatrix();
	return projectionMatrix * glm::mat4_cast(glm::inverse(transform->getRotation()));
}

glm::mat4 Camera::getViewMatrix() const {
	recalculateMatrices();
	return viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix() const {
	recalculateMatrices();
	return projectionMatrix;
}

void Camera::recalculateMatrices() const {
	projectionMatrix = glm::perspective(glm::radians(horizontalFov), ratio, nearClippingPlane, farClippingPlane);
	viewMatrix = transform->getWorldToLocalMatrix();
}

void Camera::loadSkybox(std::vector<std::string>& filenames) {
	skyboxRenderer = std::make_unique<SkyboxRenderer>(filenames);
}

void Camera::clearWithSkybox() const
{
	skyboxRenderer->render(this);
}

void Camera::clearWithSolidColor() const
{
	glClearColor(0, 0, 0, 1); // temp: black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Camera::clear() const {
	if (renderTexture)
		renderTexture->bind();
	else
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	switch(clearMethod) {
		case ClearMethod::DoNotClear:
			return;
		case ClearMethod::SolidColor:
			clearWithSolidColor();
			break;
		case ClearMethod::SkyxBox:
			glClear(GL_DEPTH_BUFFER_BIT);
			clearWithSkybox();
			break;
		default: 
			break;
	}
}

void Camera::setRenderTexture(RenderTexture* _renderTexture)
{
	if(_renderTexture == nullptr) {
		renderTexture.reset();
		return;
	}

	renderTexture = std::unique_ptr<RenderTexture>(_renderTexture);
	loadFullScreenFx();
}

void Camera::loadFullScreenFx()
{
	// 1. mesh
	quadMesh = MeshManager::getDefaultSpriteMesh();

	// 2. shader program
	fxShader = ShaderProgram::get("fxFullScreen", "shaders/ScreenFX_Vertex.glsl",
		"shaders/ScreenFX_Fragment.glsl");
}

void Camera::drawScreenFromRenderTexture()
{
	if (!renderTexture)
		return;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// draw fullscreen
	// 1. bind vao
	glBindVertexArray(quadMesh->vao);

	// 2. use program
	GLuint program = fxShader->programId();
	glUseProgram(program);

	// 3. set active textures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, renderTexture->getTextureId());

	// 4. draw 6 vertices as triangles
	glDrawArrays(GL_TRIANGLES, 0, 6);

	// 5. unbind program, texture and VAO
	glUseProgram(0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}