#ifndef TRANSFORM_h
#define TRANSFORM_h

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
private:
	glm::vec3 localPosition;
	glm::vec3 localScale;
	glm::quat localRotation;
	mutable glm::quat rotation;

	mutable glm::mat4 localToWorldMatrix;
	mutable glm::mat4 worldToLocalMatrix;

	const Transform* parent;

	void recalculateMatrices() const;
public:
	glm::vec3 getLocalPosition() const { return localPosition; };
	void setLocalPosition(glm::vec3);
	
	/* Returns world position of transform */
	glm::vec3 getPosition() const;

	glm::quat getLocalRotation() const { return localRotation; }
	glm::quat getRotation() const;
	void setLocalRotation(glm::quat);
	// YawPitchRoll is rotation Y * X * Z
	void setLocalYawPitchRoll(glm::vec3);
	void rotate(glm::vec3);
	void lookAt(glm::vec3);
	
	glm::vec3 getLocalScale() const { return localScale; };
	void setLocalScale(glm::vec3);

	const Transform* getParentTransform() const { return parent; };
	void setParent(const Transform* _parent) { parent = _parent; };

	const glm::mat4& getLocalToWorldMatrix() const;
	const glm::mat4& getWorldToLocalMatrix() const;

	glm::vec3 transformPoint(glm::vec3) const;
	glm::vec3 inverseTransformPoint(glm::vec3);
	glm::vec3 transformDirection(glm::vec3);
	glm::vec3 inverseTransformDirection(glm::vec3);

	Transform();
	~Transform();
};

#endif // TRANSFORM_h