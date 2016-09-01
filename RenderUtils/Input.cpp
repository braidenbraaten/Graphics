#include "GLFW\glfw3.h"
#include "window.h"
#include "Input.h"
#include <cstring>

 bool Input::init(const Window &window)
{
	
	memset(keys, 0, 350 * sizeof(keys));
	winHandle = window.winHandle;
	
		
	return true;
}

bool Input::step()
{
	for (int i = 0; i < 350; i++)
	{
		int res = glfwGetKey(winHandle, i);
		if((keys[i] == UP || keys[i] == RELEASE)&& res == GLFW_PRESS)
		keys[i] = PRESS;

		else if ((keys[i] == DOWN || keys[i] == PRESS) && res == GLFW_RELEASE)
		{
			keys[i] = RELEASE;
		}
		else if (keys[i] == PRESS)
		{
			keys[i] = DOWN;
		}
		else if (keys[i] == RELEASE)
		{
			keys[i] = UP;
		}
	}
	return true;
}

bool Input::term()
{
	return false;
}
