#include "AppFramework/App.h"
#include "Utils/PhysicalUnit.h"
#include "Utils/PhysicalUnitVec.h"
#include <glm/detail/qualifier.hpp>
#include <glm/glm.hpp>

int main(int argc, char* argvp[])
{
	App app;


	PhysicalUnitVec x(std::array<PhysicalUnit,3>({ PhysicalUnit(2.0f, -3), PhysicalUnit(41.0f, 2), PhysicalUnit(8.0f, 3 )}));
	auto z = x.getNormalized();

	while (!app.getWindow()->isDone())
	{
		app.handleInput();
		app.update();
		app.render();
		app.lateUpdate();
	}

	return 0;
}