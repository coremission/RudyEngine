#include "RotationBehaviour.h"
#include <System/Time.h>
#include <glm/glm.hpp>

RotationBehaviour::RotationBehaviour(GameObject* game_object)
	: Component(game_object)
{
}

void RotationBehaviour::Update()
{
	transform->rotate(glm::vec3(0.0f, 0.0f, 0.02f * Time::deltaTime)
	);
}
