#ifndef INPUT_h
#define INPUT_h

#include <Application.h>

#include <glm/glm.hpp>
#include <set>

typedef unsigned char uchar;
class Input
{
public:
	using KeyCodeType = int;
private:
	static glm::vec2 mousePosition;
	static std::set<KeyCodeType> keysPressed;
	static std::set<KeyCodeType> keysPressedThisFrame;
	static void registerKeyPressed(KeyCodeType);
	static void resetKeyPressed(KeyCodeType);

	static void reset();
public:

	inline static glm::vec2 getMousePosition() { return mousePosition; }
	static void setMouseToCenter();
	static bool checkIfKeyPressed(KeyCodeType key);
	static bool checkIfKeyDown(KeyCodeType key);
	friend class Application;
};

class KeyCodes
{
public:
	enum
	{
		A = GLFW_KEY_A,
		W = GLFW_KEY_W,
		S = GLFW_KEY_S,
		D = GLFW_KEY_D,
		P = GLFW_KEY_P,
		SPACE = GLFW_KEY_SPACE,
		PAUSEBREAK = GLFW_KEY_PAUSE,
	};
};
#endif //INPUT_h