
#include "graphics\Context.h"
#include <iostream>


int main()
{
	Context context;
	context.init();
	double x = 0, y = 0;
	while ((context.step())) // Game Loop
	{
		context.getMousePosition(x, y);
		std::cout << context.getKey('A') << std::endl;
		std::cout << x << " : " << y << std::endl;

		std::cout << context.getTime() << std::endl;
	}
	context.Terminate();
	return 0;
}