#include "Camera.h"
#include "Model/Transform.h"
#include "SkyboxRenderer.h"

#include <glm/gtx/transform.hpp>
#include <vector>
#include <memory>

// static fields
Camera* Camera::main = nullptr;

Camera::Camera(GameObject* go)
	:Component(go), 
	horizontalFov(45), 
	ratio(4.0f/3.0f), 
	nearClippingPlane(1.0f), 
	farClippingPlane(100.0f),
	clearMethod(ClearMethod::SolidColor)
{
	Camera::main = this;
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
	Camera::main = this;
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
	skyboxRenderer = std::make_unique<SkyboxRenderer>(this, filenames);
}

void Camera::clearWithSkybox() const
{
	skyboxRenderer->render();
}

void Camera::clearWithSolidColor() const
{
	glClearColor(0, 0, 0, 1); // temp: black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Camera::clear() const {
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