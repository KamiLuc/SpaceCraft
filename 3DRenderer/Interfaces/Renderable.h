#pragma once

#include <GL/glew.h>
#include <memory>

#include "../Shader/Shader.h"

class Renderable {
public:
	Renderable(const Shader& shader) : shader(shader) {};
	virtual ~Renderable() {}
	virtual void render(const UniformLocations& uniformLocations) = 0;
	const Shader& getShader() { return shader; }

protected:
	const Shader& shader;
};