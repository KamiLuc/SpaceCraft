#pragma once

#include <GL/glew.h>
#include <memory>

#include "../Shader/Shader.h"

class Renderable {
public:
	Renderable(std::shared_ptr<Shader> shader) : shader(shader) {};
	virtual ~Renderable() {}
	virtual void render(const UniformLocations& uniformLocations) = 0;
	std::shared_ptr<Shader> getShader() { return shader; }

protected:
	std::shared_ptr<Shader> shader;
};