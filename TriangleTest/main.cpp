#include "window.h"

//this is the develop branch!

int main()
{
	Window window;
	window.init();
	while (window.step());


	window.term();

	return 0;
}