#ifndef BRICKBEHAVIOUR_h
#define BRICKBEHAVIOUR_h
#include <Model/Component.h>
#include <Model/GameObject.h>

#include <glm/glm.hpp>

class BrickBehaviour: public Component
{
public:
	float halfWidth;
	float halfHeight;

	explicit BrickBehaviour(GameObject* game_object);
	void Start() override;
	void Update() override;
	~BrickBehaviour() override;

	void setHalfSize(float, float);
	glm::vec3 position() const { return gameObject->transform->getLocalPosition(); }
	float top() const { return position().y + halfHeight; }
	float bottom() const { return position().y - halfHeight; }
	float left() const { return position().x - halfWidth; }
	float right() const { return position().x + halfWidth; }
};

#endif //BRICKBEHAVIOUR_h