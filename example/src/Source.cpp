#include "GLFWExample.h"
int main()
{
 	GLFWWindowManager ui;
	ui.AddWindow(std::unique_ptr<exampleWindow>(new exampleWindow()));
	while (!ui.shouldClose())
	{
		ui.Update();
	}
	return 0;
}