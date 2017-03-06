#ifndef CAMERA_h
#define CAMERA_h

#include <Rendering/rendering.hpp>
#include <Model/Component.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>

class Camera: public Component
{
	static Camera * main;

private:
	float horizontalFov;
	float ratio; // width/height;
	float nearClippingPlane;
	float farClippingPlane;
	std::unique_ptr<IRenderer> skyboxRenderer;
	mutable glm::mat4 viewMatrix;
	mutable glm::mat4 projectionMatrix;

	void recalculateMatrices() const;
public:
	explicit Camera(GameObject*);
	Camera(GameObject*, float, float, float, float);
	virtual void Update() override;
	virtual void Start() override;
	glm::mat4 getViewProjectionMatrix() const;
	glm::mat4 getOrientationMatrix() const;
	float getHorizontalFov() const { return horizontalFov; }
	float getRatio() const { return ratio; }
	glm::mat4 getViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	void loadSkybox(std::vector<std::string>& filenames);
	void clearWithSkybox() const;
	static const Camera * getMainCamera() { return main; }
};

#endif //CAMERA_h