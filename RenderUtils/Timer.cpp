#include "GLFW\glfw3.h"
#include "Timer.h"

bool Timer::init()
{
	//start clock at 0
	glfwSetTime(0);

	currentTime = 0;
	prevTime    = 0;
	deltaTime   = 0;
	return true;
}

bool Timer::step()
{
	currentTime = getRealTime();
	deltaTime   = currentTime - prevTime;
	prevTime	= currentTime;
	return true;
}

bool Timer::term()                {return true;}

float Timer::getDeltaTime() const {return deltaTime;}

float Timer::getTotalTime() const {return currentTime;}

float Timer::getRealTime()  const {return glfwGetTime();}
