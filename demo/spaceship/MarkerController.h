#pragma once
#include <Model/Component.h>

class MarkerController: public Component
{
	Transform* target;
public:
	explicit MarkerController(GameObject* gameObject);
	virtual ~MarkerController() override;
	virtual void Update() override;
	void setTarget(Transform * newTarget);
};
