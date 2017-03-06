#ifndef GAMEOBJECT_h
#define GAMEOBJECT_h

#include <Rendering/BaseRenderer.h>
#include "Component.h"
#include "Transform.h"

#include <vector>
#include <string>
#include <memory>

class Component;
class IRenderer;

class GameObject {
private:
	std::vector<std::unique_ptr<Component>> components;
public:
	std::string name;
	std::unique_ptr<Transform> transform;
	std::unique_ptr<IRenderer> renderer;

	GameObject();
	explicit GameObject(const std::string& _name);
	GameObject(const GameObject& m);
	~GameObject();
	void Update();
	template<typename T> void AddComponent();
	template<typename T> void AddComponent(T*);
private:
	void operator=(const GameObject&) = delete;
};

template<typename T> void GameObject::AddComponent() {
	auto component = std::make_unique<T>(this);
	component->Start();
	components.push_back(move(component));
}

template<typename T> void GameObject::AddComponent(T* _component) {
	std::unique_ptr<T> component(_component);
	component->Start();
	components.push_back(move(component));
}
#endif // GAMEOBJECT_h
