#ifndef TIME_h
#define TIME_h

#include <Application.h>

class Time
{
private:
	static void updateClock();
public:
	static float time;
	static float realTimeSinceStartup;
	static float deltaTime;
	friend class Application;
};

#endif //TIME_h