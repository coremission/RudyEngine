#include "BallBehaviour.h"
#include <iostream>
#include <System/system.hpp>

BallBehaviour::BallBehaviour(GameObject* _gameObject)
	:Component(_gameObject),
	velocity({0, 0, 0}),
	pause(false),
	radius(0)
{
}

void BallBehaviour::Update()
{
	if(Input::checkIfKeyDown(KeyCodes::SPACE)) {
		pause = !pause;
		std::cout << "pause is " << (pause ? "on" : "off") << std::endl;
		return;
	}

	if (pause)
		return;

	gameObject->transform->setLocalPosition(position() + velocity);

	//if (left() < -1 || right() > 1)
	//	velocity.x = -velocity.x;
	
    //if (top() > 1 || bottom() < -1)
	//	velocity.y = -velocity.y;
    
    //if (position().z < -1 || position().z > 1)
    //    velocity.z = -velocity.z;
}

void BallBehaviour::Start()
{
	velocity = { 0.000f, 0.001f, 0.001f};
	radius = 0.02f;
	gameObject->transform->setLocalScale(glm::vec3(radius, radius, 1));
}

void BallBehaviour::negativeVelocityY()
{
	if(velocity.y > 0)
		velocity.y = -velocity.y;
}

void BallBehaviour::positiveVelocityY()
{
	if (velocity.y < 0)
		velocity.y = -velocity.y;
}

void BallBehaviour::negativeVelocityX()
{
	if(velocity.x > 0)
		velocity.x = -velocity.x;
}

void BallBehaviour::positiveVelocityX()
{
	if (velocity.x < 0)
		velocity.x = -velocity.x;
}
