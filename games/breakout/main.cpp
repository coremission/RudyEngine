#include "BallBehaviour.h"
#include "Controller.h"
#include "PaddleBehaviour.h"

#include <Rendering/SpriteRenderer.h>
#include <Rendering/Camera.h>

#include <Application.h>
#include <iostream>
#include <memory>

using namespace std;

void _do(int, char**);
void setUpScene();

int main(int argc, char **argv)
{
	_do(argc, argv);
	cout << endl << "Press any key to exit..." << endl;
	cin.get();

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
	ball->renderer = make_unique<SpriteRenderer>(ball, "Sprites\\ball.png");
	
	// PADDLE
	GameObject* paddle = new GameObject("paddle");
	PaddleBehaviour* paddleBehaviour = new PaddleBehaviour(paddle);
	paddleBehaviour->setUpBall(ballBehaviour);
	paddle->AddComponent(paddleBehaviour);
	paddle->renderer = make_unique<SpriteRenderer>(paddle, "Sprites\\paddle.png");
	
	// CONTROLLER
	GameObject* controller = new GameObject("controller");
	Controller* controllerBehaviour = new Controller(controller, ballBehaviour);
	controller->AddComponent<Controller>(controllerBehaviour);

	// TODO: add camera
	// CAMERA
	GameObject* camera = new GameObject("camera");
	camera->AddComponent<Camera>();
}