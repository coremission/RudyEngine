#include "Input.h"
#include <set>

using namespace std;

// static fields
glm::vec2 Input::mousePosition;
set<Input::KeyCodeType> Input::keysPressed;
set<Input::KeyCodeType> Input::keysPressedThisFrame;

void removeFromSet(set<Input::KeyCodeType>& someSet, Input::KeyCodeType key)
{
	for (auto it = someSet.begin(); it != someSet.end();) {
		if (*it == key) {
			someSet.erase(it);
			return;
		}
		++it;
	}
}

void Input::registerKeyPressed(KeyCodeType key)
{
	if (key == KeyCodes::PAUSEBREAK)
		exit(0);
	
	if (!checkIfKeyPressed(key)) {
		keysPressedThisFrame.insert(key);
		keysPressed.insert(key);
	}
}

void Input::resetKeyPressed(KeyCodeType key)
{
	removeFromSet(keysPressed, key);
	removeFromSet(keysPressedThisFrame, key);
}

void Input::setMouseToCenter()
{
	Application::setMouseCursorToCenter();
}

bool Input::checkIfKeyPressed(KeyCodeType key)
{
	return find(keysPressed.begin(), keysPressed.end(), key) != keysPressed.end();
}

bool Input::checkIfKeyDown(KeyCodeType key)
{
	return find(keysPressedThisFrame.begin(), keysPressedThisFrame.end(), key) != keysPressedThisFrame.end();
}

void Input::reset()
{
	keysPressedThisFrame.clear();
}