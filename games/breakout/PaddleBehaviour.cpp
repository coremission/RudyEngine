#include "PaddleBehaviour.h"
#include <System/Input.h>

PaddleBehaviour::PaddleBehaviour(GameObject* go)
	:Component(go),
	halfWidth(0),
	halfHeight(0), 
	ball(nullptr)
{
}

void PaddleBehaviour::Start()
{
	halfWidth = 0.2f;
	halfHeight = 0.05f;
	gameObject->transform->setLocalScale(glm::vec3(halfWidth, halfHeight, 1));
	gameObject->transform->setLocalPosition(glm::vec3(0, -0.8f, 0));
}

void PaddleBehaviour::Update()
{
	const static glm::vec2 sensitivity = glm::vec2(0.0005f, 0);
	gameObject->transform->setLocalPosition(position() + glm::vec3(velocity.x, velocity.y, 0));
	velocity = glm::vec2(0, 0);

	if(Input::checkIfKeyPressed(KeyCodes::A) && left() > -1) 	{
		velocity = glm::vec2(-sensitivity.x, sensitivity.y);
	}
	if (Input::checkIfKeyPressed(KeyCodes::D) && right() < 1) {
		velocity = glm::vec2(sensitivity.x, sensitivity.y);
	}

	// check collision
	if(ball->bottom() < top() && 
		(ball->right() > left() && ball->left() < right())) {
		ball->positiveVelocityY();
	}
}

void PaddleBehaviour::setUpBall(BallBehaviour * _ball)
{
	ball = _ball;
}

PaddleBehaviour::~PaddleBehaviour()
{
}
