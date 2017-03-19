#ifndef INPUT_h
#define INPUT_h

#include <Application.h>

#include <glm/glm.hpp>
#include <set>

typedef unsigned char uchar;
class Input
{
	typedef int KeyCodeType;
private:
	static glm::vec2 mousePosition;
	static std::set<KeyCodeType> keysPressed;
	static void registerKeyPressed(KeyCodeType);
	static void resetKeyPressed(KeyCodeType);
public:
	inline static glm::vec2 getMousePosition() { return mousePosition; }
	static void setMouseToCenter();
	static bool checkIfKeyPressed(KeyCodeType key);
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
		SPACE = GLFW_KEY_SPACE,
	};
};
#endif //INPUT_h