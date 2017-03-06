#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

Component::Component(GameObject* _gameObject):
	gameObject(_gameObject), transform(_gameObject->transform.get())
{
}

void Component::Start()
{
}

void Component::Update()
{
}

Component::~Component()
{
}
