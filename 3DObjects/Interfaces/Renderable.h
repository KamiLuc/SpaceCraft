#pragma once

#include "../../3DRenderer/Shader/Shader.h"

class Renderable {
public:
	Renderable(const Shader& shader) : shader(&shader) {};
	virtual ~Renderable() {}
	virtual void render(const UniformLocations& uniformLocations) = 0;

	void setShader(const Shader& shader) { this->shader = &shader; }
	const Shader& getShader() const { return *shader; }

protected:
	const Shader* shader;
};