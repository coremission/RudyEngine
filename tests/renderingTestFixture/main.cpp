#include <Rendering/SpriteRenderer.h>
#include <Rendering/Camera.h>
#include <Application.h>
#include <System/system.hpp>

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
	GameObject* tempGo = new GameObject("temp");
	tempGo->renderer = make_unique<SpriteRenderer>(tempGo, "Sprites\\drakeq_up.dds");
}