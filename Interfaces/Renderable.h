#pragma once

#include "../../3DRenderer/Shader/UniformLocations.h"
#include "../../3DRenderer/Shader/Shader.h"

#include <glm/glm.hpp>

class Renderable {
public:
	Renderable(const Shader& shader)
		: shader(&shader) {};
	virtual ~Renderable() {}

	virtual void render(const UniformLocations& uniformLocations) const = 0;
	virtual glm::mat4 getModelMatrix() const = 0;

	void setShader(const Shader& shader) { this->shader = &shader; }
	const Shader& getShader() const { return *shader; }

protected:
	const Shader* shader;
};


