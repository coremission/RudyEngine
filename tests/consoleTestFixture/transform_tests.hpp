#ifndef TRANSFORM_TESTS_HPP
#define TRANSFORM_TESTS_HPP

#include "testfixture.hpp"

void localToWorld_Test()
{
	/*
	TODO: MUST IMPLEMENT World 2 Local, Local 2 World
	and make proper tests for TransformPoint, and InverseTransformPoint
	*/

	vec3 offset2 = vec3(0.0f, 0.0f, 2.0f);
	vec3 offset = vec3(0.0f, 0.0f, 1.0f);

	GameObject* point = new GameObject("point");
	point->transform->setLocalPosition(offset);

	assert_equal(offset, point->transform->transformPoint(vec3(0.0f, 0.0f, 0.0f)));
	assert_equal(-offset, point->transform->inverseTransformPoint(vec3(0.0f, 0.0f, 0.0f)));

}
#endif //TRANSFORM_TESTS_HPP