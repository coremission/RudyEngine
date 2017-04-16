#include "MarkerController.h"
#include <glm/glm.hpp>
#include <System/Time.h>
#include <rudymath.hpp>

MarkerController::MarkerController(GameObject* gameObject)
	:Component(gameObject), target(nullptr)
{
}

MarkerController::~MarkerController()
{
}


void MarkerController::Update()
{
	/* todo: temporary commented
	static float nextUpdateTime = 0.0f;
	if (nextUpdateTime > Time::time)
		return;
	
	nextUpdateTime = Time::time + 0.01f;

	float speed = 0.005f * Time::deltaTime;
	transform->setLocalPosition(transform->getLocalPosition() +
		transform->transformDirection(glm::vec3(1, 1, 0)) * speed);

	auto mvpMatrix = Camera::getMainCamera()->getViewProjectionMatrix() * target->getLocalToWorldMatrix();

	auto point4 = mvpMatrix * glm::vec4(transform->transformPoint(glm::vec3(0, 0, 0)), 1);
	auto point = glm::vec3(point4.x / point4.w, point4.y / point4.w, point4.z / point4.w);
	
	if(point4.z < 0)
		point.y = -1.0f;
	
	point.x = rudy::clamp(point.x, -1, 1);
	point.y = rudy::clamp(point.y, -1, 1);

	transform->setLocalPosition(glm::vec3(point.x, point.y, 0));
	*/
}

void MarkerController::setTarget(Transform* newTarget)
{
	target = newTarget;
}