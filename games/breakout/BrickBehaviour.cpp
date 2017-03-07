#include "BrickBehaviour.h"

BrickBehaviour::BrickBehaviour(GameObject* game_object)
	:Component(game_object)
{
}

void BrickBehaviour::Start()
{
}

void BrickBehaviour::Update()
{
}

BrickBehaviour::~BrickBehaviour()
{
}

void BrickBehaviour::setHalfSize(float _halfWidth, float _halfHeight)
{
	halfWidth = _halfWidth;
	halfHeight = _halfHeight;
	gameObject->transform->setLocalScale(glm::vec3(halfWidth, halfHeight, 1));
}
