#pragma once
#include <SDL.h>
class Timer
{
public:
	Timer() {};

	float GetTimeInMilliseconds() { return (float)SDL_GetTicks(); }
	float GetTimeInSeconds() { return GetTimeInMilliseconds() * 0.001; }
	void SetDeltaTime()
	{
		float time = GetTimeInSeconds();
		deltaTime = time - lastTime;
		lastTime = time;
	}
	float GetDeltaTime() { return deltaTime; }

	operator float() const { return deltaTime; }

private:
	float lastTime = 0;
	float deltaTime = 0;
};

