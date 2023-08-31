#include "AppFramework/App.h"
#include "Utils/CircularVector.h"
#include "Utils/PhysicalUnit.h"


int main(int argc, char* argvp[])
{
	App app;

	CircularVector<PhysicalUnit> lv(4);

	for (int i = 0; i < 8; ++i) {
		lv.push(PhysicalUnit(1.2f,i));
	}

	lv.print(std::cout);

	while (!app.getWindow()->isDone())
	{
		app.handleInput();
		app.update();
		app.render();
		app.lateUpdate();
	}

	return 0;
}