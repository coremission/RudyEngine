#pragma once
#include <Model/Component.h>
#include <Model/GameObject.h>

class MoveBehaviour : public Component
{
public:
	explicit MoveBehaviour(GameObject*);
	virtual void Update() override;
};
