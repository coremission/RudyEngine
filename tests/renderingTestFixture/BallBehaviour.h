#ifndef BALLBEHAVIOUR_h
#define BALLBEHAVIOUR_h
#include <Model/Component.h>
#include <Model/GameObject.h>

#include <glm/glm.hpp>

class BallBehaviour: public Component
{
private:
	glm::vec3 velocity;
public:
	float radius;
	glm::vec3 position() const { return gameObject->transform->getLocalPosition(); }
	float top() const { return position().y + radius; }
	float bottom() const { return position().y - radius; }
	float left() const { return position().x - radius; }
	float right() const { return position().x + radius; }

	explicit BallBehaviour(GameObject*);
	virtual void Update() override;
	virtual void Start() override;

	void negativeVelocityY();
	void positiveVelocityY();

	void negativeVelocityX();
	void positiveVelocityX();
};

#endif // BALLBEHAVIOUR_h
