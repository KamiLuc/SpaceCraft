#pragma once

#include "3DRenderer/SceneContext.h"

class Renderable {
public:
	Renderable() {};
	virtual ~Renderable() {}

	virtual void render(SceneContext& sceneContext) const = 0;
};


