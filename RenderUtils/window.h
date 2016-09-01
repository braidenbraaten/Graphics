#pragma once

class Window
{
private:
	friend class Input;

	int width, height;
	char title[64];
	bool isInitialized = false;

	//forward declare
	struct GLFWwindow *winHandle = nullptr;

public:

	bool init(int a_width = 800, int a_height = 600, char *a_title = "I am Default"); // setup, start, initialize
	bool step();										 // update, refresh
	bool term();										 // kill, terminate, DIEDIEDIE

};