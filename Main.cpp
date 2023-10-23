#include "AppFramework/App.h"

int main(int argc, char* argvp[])
{
	App app;

	while (!app.getWindow()->isDone())
	{
		app.update();
		app.render();
		app.lateUpdate();
	}

	return 0;
}