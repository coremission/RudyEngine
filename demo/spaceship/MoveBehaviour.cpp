#include "MoveBehaviour.h"
#include <glm/glm.hpp>

MoveBehaviour::MoveBehaviour(GameObject* game_object)
	: Component(game_object)
{
}

void MoveBehaviour::Update()
{
	//transform->setLocalPosition(transform->getLocalPosition() + glm::vec3(0, 0, 0.001f));
}
