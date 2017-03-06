#include "Time.h"
#include <ctime>

float Time::time = 0;
float Time::deltaTime = 0;
float Time::realTimeSinceStartup = 0;

void Time::updateClock()
{
	static clock_t ticks = 0;
	clock_t newTicks = clock();
	deltaTime = (float)((long double)(newTicks - ticks) / (long double)CLOCKS_PER_SEC);
	ticks = newTicks;
	realTimeSinceStartup += deltaTime;
	time += deltaTime;
}
