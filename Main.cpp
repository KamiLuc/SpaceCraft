#include "AppFramework/App.h"
#include "Utils/PhysicalUnit.h"
#include "Utils/PhysicalUnitVec.h"
#include <glm/detail/qualifier.hpp>
#include <glm/glm.hpp>

int main(int argc, char* argvp[])
{
	PhysicalUnit a(10.3f, 4);
	PhysicalUnit b(12.3f, 5);


	auto aa = a + b;
	auto aaa = a * b;
	auto aaaa = a - b;
	auto aaaaa = a / b;
	
	PhysicalUnitVec<2> v1{ {a,b} };
	PhysicalUnitVec<2> v2{ {a,b} };

	auto c = v1 * v2;
	auto d = v1 / v2;

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