#include <Application.h>
#include <Model/ModelLoader.h>
#include <iostream>
#include "RotationBehaviour.h"
#include "CameraController.h"
#include <System/system.hpp>
#include <Rendering/SpriteRenderer.h>
#include <Rendering/OverlayRenderer.h>
#include "MarkerController.h"
#include <Rendering/TrailRenderer.h>
#include "MoveBehaviour.h"

using namespace std;

void _do(int, char**);
void setUpScene();
constexpr float  PI = 3.14159265358979f;

int main(int argc, char **argv)
{
	_do(argc, argv);

	// todo: temporary
	//cout << endl << "Press any key to exit..." << endl;
	//cin.get();

	return 0;
}

// this one exist to see destructors outputs
void _do(int argc, char **argv) {
	try {
		Application::initialize(&argc, argv);
		setUpScene();
		Application::runMainLoop();
		Application::exit();
	}
	catch (exception exc) {
		Application::leaveMainLoop();
		Application::exit();
		cout << exc.what();
	}
}

void setUpScene()
{
	// load space station
	auto spaceStation = ModelLoader::LoadModel("station", "assets/spacestation/space_station_4.obj",
		"assets/spacestation/space_station_4_diffuse.png");
	spaceStation->transform->setLocalPosition(glm::vec3(0, 0, -1800));

	GameObject* spaceShipRootGo = new GameObject("spaceshipRoot");
	auto spaceShipGo = ModelLoader::LoadModel("spaceCruiser", "assets/space_cruiser_4.obj", "assets/space_cruiser_4_color.png");
	GameObject* cameraGo = new GameObject("camera");
	float screenRatio = static_cast<float>(Screen::width) / static_cast<float>(Screen::height);
	
	Camera* camera = new Camera(cameraGo, 60.0f, screenRatio, 0.1f, 10000.0f);
	cameraGo->AddComponent(camera);

	GameObject* crosshair = new GameObject("crosshair");
	constexpr float crosshairSize = 0.03f;
	crosshair->transform->setLocalScale(glm::vec3(crosshairSize, crosshairSize * screenRatio, 1));
	crosshair->renderer = std::make_unique<OverlayRenderer>(crosshair, "assets/crosshair.png");

	// some object
	GameObject* object = new GameObject("object");
	object->AddComponent(new MoveBehaviour(object));
	object->transform->setParent(spaceShipRootGo->transform.get());
	object->transform->setLocalPosition(glm::vec3(0, 0, 5));

	GameObject* trail = new GameObject("trail");
	trail->transform->setParent(object->transform.get());
	trail->renderer = make_unique<TrailRenderer>(trail, 55, 10.0f, "sprites/checkerboard.png");

	GameObject* marker = new GameObject("stationMarker");
	marker->renderer = std::make_unique<OverlayRenderer>(marker, "assets/crosshair.png");
	constexpr float markerSize = 0.04f;
	MarkerController* markerController = new MarkerController(marker);
	marker->AddComponent(markerController);
	marker->transform->setLocalScale(glm::vec3(markerSize, markerSize * screenRatio, 1));
	markerController->setTarget(object->transform.get());

	/*
	GL_TEXTURE_CUBE_MAP_POSITIVE_X
	GL_TEXTURE_CUBE_MAP_NEGATIVE_X
	GL_TEXTURE_CUBE_MAP_POSITIVE_Y
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
	GL_TEXTURE_CUBE_MAP_POSITIVE_Z
	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	*/
	auto filenames = std::vector<string>{
		"assets/Skyboxes/mp_drakeq/drakeq_rt.png",
		"assets/Skyboxes/mp_drakeq/drakeq_lf.png",
		"assets/Skyboxes/mp_drakeq/drakeq_up.png",
		"assets/Skyboxes/mp_drakeq/drakeq_dn.png",
		"assets/Skyboxes/mp_drakeq/drakeq_bk.png",
		"assets/Skyboxes/mp_drakeq/drakeq_ft.png",
	};

	camera->loadSkybox(filenames);
	
	// automatic rotation
	//	RotationBehaviour* rotation = new RotationBehaviour(spaceShipRootGo);
	//	spaceShipRootGo->AddComponent<RotationBehaviour>(rotation);

	spaceShipGo->transform->setParent(spaceShipRootGo->transform.get());

	CameraController* cameraController = new CameraController(spaceShipRootGo);
	spaceShipRootGo->AddComponent(cameraController);
	
	// todo: here is an issue with vp matrix
	// Place camera behing ship
	spaceShipGo->transform->setLocalPosition(glm::vec3(0, 0, -20));
	spaceShipGo->transform->rotate(glm::vec3(0, -PI / 2.0f, 0));
	camera->transform->setParent(spaceShipRootGo->transform.get());
	camera->transform->setLocalPosition(glm::vec3(0, 20, 50));
	camera->setClearMethod(ClearMethod::SkyxBox);
	
	// use local position because ship is root transform
	//camera->transform->lookAt(spaceShipGo->transform->getLocalPosition());
}