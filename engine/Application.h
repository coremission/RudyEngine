#ifndef APPLICATION_h
#define APPLICATION_h
#include "Model/GameObject.h"
#include "Model/Scene.h"
#include <glfw/glfw3.h>
#include "Rendering/Camera.h"

class Application
{
private:
	static GLFWwindow* window;
	static std::unique_ptr<Models::Scene> scene;
	static Camera* camera;

	static void renderScene();

	static void processMousePress(int, int, int, int);
	static void processMousePressedMove(int, int);
	static void drawGameObject(GameObject&);
	Application() = delete;
	Application(const Application&) = delete;
	const Application& operator=(Application&) = delete;

	// glfw callbacks
	static void processKeyboard(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void processMouseFreeMove(GLFWwindow*, double, double);

public:
	static void setCamera(Camera * _camera) { camera = _camera; }

	static void initialize(int* argc, char** argv);
	static void runMainLoop();
	static void leaveMainLoop();
	static void setMouseCursorToCenter();
	static void exit();

	friend class GameObject;
};

#endif // APPLICATION_h