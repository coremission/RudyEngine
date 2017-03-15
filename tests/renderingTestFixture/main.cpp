#include "BallBehaviour.h"
#include <Rendering/Camera.h>
#include <Rendering/SpriteRenderer.h>
#include <Application.h>
#include <System/system.hpp>

#include <iostream>
#include <memory>
#include <Rendering/TrailRenderer.h>

using namespace std;

void _do(int, char**);
void setUpScene();

int main(int argc, char **argv)
{
	_do(argc, argv);
    
    // todo: disabled for a while
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

void setUpScene() {
    // BALL
    GameObject* ball = new GameObject("ball");
    BallBehaviour* ballBehaviour = new BallBehaviour(ball);
    ball->AddComponent<BallBehaviour>(ballBehaviour);
    // create renderer
    ball->renderer = make_unique<SpriteRenderer>(ball, "sprites/ball.png");

    GameObject* tempGo = new GameObject("temp");
	tempGo->renderer = make_unique<TrailRenderer>(tempGo);
	tempGo->renderer->update();
    
    // TODO: add camera
    // CAMERA
    GameObject* camera = new GameObject("camera");
    camera->AddComponent<Camera>();
}
