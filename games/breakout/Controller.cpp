#include "Controller.h"
#include <Model/Component.h>
#include "BrickBehaviour.h"
#include <Rendering/SpriteRenderer.h>
#include <System/Time.h>

#include <cmath>
#include <memory>

constexpr float diff = 0.0001f;

Controller::Controller(GameObject* go, BallBehaviour* _ball):
	Component(go),
	ball(_ball)
{

}

void Controller::Update()
{
	// check collisions
	for (auto brick : bricks) {
		glm::vec3 distance = ball->position() - brick->position();
		
		bool fitHorizontal = abs(distance.x) < ball->radius + brick->halfWidth;
		bool fitVertical = abs(distance.y) < ball->radius + brick->halfHeight;
		bool aboveBrick = distance.y > 0 && ball->top() > brick->top();
		bool belowBrick = distance.y < 0 && ball->bottom() < brick->bottom();
		bool fromRight  = distance.x > 0;
		bool fromLeft   = distance.x < 0;
		// from above
		if (aboveBrick && fitHorizontal && fitVertical) {
			ball->positiveVelocityY();
			std::cout << "above" << std::endl;
			continue;
		}
		// from below
		if (belowBrick && fitHorizontal && fitVertical) {
			ball->negativeVelocityY();
			std::cout << "below" << std::endl;
			continue;
		}
		// from right
		if (fromRight && fitHorizontal && fitVertical) {
			ball->positiveVelocityX();
			continue;
		}
		// from left
		if (fromLeft && fitHorizontal && fitVertical) {
			ball->negativeVelocityX();
			continue;
		}
	}

	static float lastTimeShown = 0;
	constexpr float frequency = 3.0f;

	if (Time::realTimeSinceStartup > lastTimeShown + frequency)
	{
		lastTimeShown = Time::realTimeSinceStartup;
		std::cout << "fps: " << 1.0f / Time::deltaTime << std::endl;
	}
}

void Controller::Start()
{
	glm::vec3 start(-0.8f, 0.8f, 0);
	glm::vec3 offset(0.15f, -0.3f, 0);
	float halfWidth = 0.1f;
	float halfHeight = 0.06f;

	GameObject* tempRoot = new GameObject("tempRoot");
	tempRoot->transform->setLocalPosition(glm::vec3(0, 0, 0));
	ball->gameObject->transform->setParent(tempRoot->transform.get());

	for(int i = 0; i < 1; ++i) {
		for (int j = 0; j < 6; ++j) {
			GameObject* brick = new GameObject("brick" + std::to_string(i) + std::to_string(j));
			BrickBehaviour* brickBehaviour = new BrickBehaviour(brick);
			brickBehaviour->setHalfSize(halfWidth, halfHeight);
			brick->transform->setParent(tempRoot->transform.get());
			brick->transform->setLocalPosition(start + glm::vec3(offset.x * j, offset.y * i, start.z));
			brick->AddComponent(brickBehaviour);
			brick->renderer = std::make_unique<SpriteRenderer>(brick, "sprites/brick.png");
			bricks.push_back(brickBehaviour);
		}
	}
}

Controller::~Controller() {

}
