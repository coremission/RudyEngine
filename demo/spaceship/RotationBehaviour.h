#pragma once
#include <Model/Component.h>
#include <Model/GameObject.h>

class RotationBehaviour: public Component
{
public:
	explicit RotationBehaviour(GameObject*);
	virtual void Update() override;
};
