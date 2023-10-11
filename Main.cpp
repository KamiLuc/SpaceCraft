#include "AppFramework/App.h"

#include "AppFramework/StateManager/StateManager.h"
#include "AppFramework/Serializer/Serializer.h"

int main(int argc, char* argvp[])
{
	App app;

	while (!app.getWindow()->isDone())
	{
		app.handleInput();
		app.update();
		app.render();
		app.lateUpdate();
	}

	return 0;
}