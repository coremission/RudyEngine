#include "testfixture.hpp"

void projectionMatrix_Test()
{
	GameObject* point = new GameObject("someObject");
	point->transform->setLocalPosition(vec3(0.0f, 0.0f, -2.0f));

	GameObject* cameraGo = new GameObject("camera");
	Camera* camera = new Camera(cameraGo, 60.0f, 4.0f / 3.0f, 1.0f, 100.0f);
	cameraGo->AddComponent(camera);
	camera->transform->setLocalPosition(vec3(0.0f, 0.0f, 0.0f));

	cout << "someObject position: " << point->transform->getLocalPosition() << endl;
	vec3 localPoint = vec3(0.0f, 0.0f, 0.0f);
	cout << "some local point: " << localPoint << endl;

	mat4 modelingMatrix = point->transform->getLocalToWorldMatrix();
	cout << "modeling matrix: " << endl << modelingMatrix << endl;

	cout << "world coordinates : " << modelingMatrix * vec4(localPoint, 1.0f) << endl;
	mat4 viewMatrix = camera->getViewMatrix();
	cout << "view matrix: " << endl;
	cout << viewMatrix << endl;
	
	cout << "in view coordinates: " << viewMatrix * modelingMatrix * vec4(localPoint, 1.0f) << endl;

	cout << endl << "projection: " << endl;
	mat4 mvp = camera->getViewProjectionMatrix();
	
	cout << "mvp: " << endl;
	cout << mvp << endl;

	vec4 result = mvp * modelingMatrix * vec4(localPoint, 1.0f);

	auto divided = vec3(result.x / result.w, result.y / result.w, result.z / result.w);

	cout << "result: " << result << endl;
	cout << "after division: " << divided << endl;
}