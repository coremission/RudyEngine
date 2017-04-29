#ifndef CAMERA_CONTROLLER_h
#define CAMERA_CONTROLLER_h
#include <Model/Component.h>

class CameraController: public Component
{
public:
	explicit CameraController(GameObject* game_object);

	virtual void Update() override;
	virtual void Start() override;
};

#endif //CAMERA_CONTROLLER_h