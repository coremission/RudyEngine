#include "CameraController.h"
#include <System/system.hpp>

using namespace glm;

CameraController::CameraController(GameObject* game_object)
	: Component(game_object)
{
}

void CameraController::Start()
{
}

void CameraController::Update()
{
	//float speed = -45 * Time::deltaTime;
	//transform->setLocalPosition(transform->getLocalPosition() + transform->transformDirection(vec3(0, 0, 1)) * speed);
	
	if (Input::checkIfKeyPressed(KeyCodes::D)) {
		transform->rotate(vec3(0.0f, -0.01f, 0.0f));
	}
	if (Input::checkIfKeyPressed(KeyCodes::A)) {
		transform->rotate(vec3(0.0f, 0.01f, 0.0f));
	}
	if (Input::checkIfKeyPressed(KeyCodes::W)) {
		transform->rotate(vec3(-0.01f, 0.0f, 0.0));
	}
	if (Input::checkIfKeyPressed(KeyCodes::S)) {
		transform->rotate(vec3(0.01f, 0.0f, 0.0));
	}
}