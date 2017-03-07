#ifndef PADDLEBEHAVIOUR_h
#define PADDLEBEHAVIOUR_h

#include "BallBehaviour.h"

#include <Model/Component.h>
#include <memory>

class PaddleBehaviour: public Component
{
private:
	float halfWidth;
	float halfHeight;
	glm::vec2 velocity;
	BallBehaviour* ball;
public:

	glm::vec3 position() const { return gameObject->transform->getLocalPosition(); }
	float top() const { return position().y + halfHeight; }
	float bottom() const { return position().y - halfHeight; }
	float left() const { return position().x - halfWidth; }
	float right() const { return position().x + halfWidth; }

	explicit PaddleBehaviour(GameObject*);
	void Start() override;
	void Update() override;
	void setUpBall(BallBehaviour*);
	~PaddleBehaviour() override;
};
#endif //PADDLEBEHAVIOUR_h