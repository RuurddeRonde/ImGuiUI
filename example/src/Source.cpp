#include "GLFWExample.h"
int main()
{
 	GLFWWindowManager ui;

	while (!ui.shouldClose())
	{
		ui.Update();
	}
	return 0;
}